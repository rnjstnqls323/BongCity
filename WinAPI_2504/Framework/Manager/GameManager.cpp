#include "Framework.h"

#include "Scenes/ExampleScene/ModelExportScene.h"
#include "Scenes/ExampleScene/ModelRenderScene.h"
#include "Scenes/ExampleScene/ModelAnimaionScene.h"
#include "Scenes/ExampleScene/CharacterScene.h"
#include "Scenes/ExampleScene/ModelInstancingScene.h"
#include "Scenes/ExampleScene/TerrainScene.h"
#include "Scenes/ExampleScene/TerrainEditorScene.h"

GameManager::GameManager()
{
	Create();
		
	SCENE->AddScene("Export", new ModelExportScene());
	SCENE->AddScene("Game", new ModelRenderScene());
	//SCENE->AddScene("Game", new ModelAnimationScene());
	//SCENE->AddScene("Game", new CharacterScene());
	//SCENE->AddScene("Game", new ModelInstancingScene());
	//SCENE->AddScene("Game", new TerrainScene());
	//SCENE->AddScene("Game", new TerrainEditorScene());

	SCENE->ChangeScene("Game");
}

GameManager::~GameManager()
{
	Release();
}

void GameManager::Update()
{
	Timer::Get()->Update();
	Input::Get()->Update();
	Audio::Get()->Update();

	Environment::Get()->Update();

	SCENE->Update();

	InvalidateRect(hWnd, nullptr, false);
}

void GameManager::Render()
{
	SCENE->PreRender();
	
	
	Device::Get()->Clear();	

	Environment::Get()->SetRender();
	SCENE->Render();

	Environment::Get()->SetPostRender();
	SCENE->PostRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());

	Environment::Get()->Edit();

	SCENE->GUIRender();	

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void GameManager::Create()
{
	Timer::Get();
	Input::Get();
	Audio::Get();

	Device::Get();

	SceneManager::Get();

	Environment::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Release()
{
	Timer::Delete();
	Input::Delete();

	Device::Delete();
	Shader::Delete();
	Texture::Delete();
	Audio::Delete();

	SceneManager::Delete();

	Environment::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}

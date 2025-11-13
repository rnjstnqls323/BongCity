#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	TileManager::Get();
	InstallationManager::Get();
	UIManager::Get();
}

TestScene::~TestScene()
{
	TileManager::Delete();
	InstallationManager::Delete();
	UIManager::Delete;
}

void TestScene::Update()
{	
	TileManager::Get()->Update();	
	UIManager::Get()->Update();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	TileManager::Get()->Render();
	InstallationManager::Get()->Render();
}

void TestScene::PostRender()
{
	UIManager::Get()->Render();
}

void TestScene::GUIRender()
{
	TileManager::Get()->Edit();
	UIManager::Get()->Edit();
}

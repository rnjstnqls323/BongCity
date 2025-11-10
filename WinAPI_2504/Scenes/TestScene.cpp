#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	TileManager::Get();
	InstallationManager::Get();
}

TestScene::~TestScene()
{
	TileManager::Delete();
	InstallationManager::Delete();
}

void TestScene::Update()
{	
	TileManager::Get()->Update();	
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
}

void TestScene::GUIRender()
{
	TileManager::Get()->Edit();
}

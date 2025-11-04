#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	TileManager::Get();
}

TestScene::~TestScene()
{
	TileManager::Delete();
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
}

void TestScene::PostRender()
{
}

void TestScene::GUIRender()
{
}

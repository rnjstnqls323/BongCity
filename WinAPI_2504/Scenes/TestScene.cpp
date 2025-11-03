#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	tile = new Tile;
}

TestScene::~TestScene()
{
	delete tile;
}

void TestScene::Update()
{
	tile->UpdateWorld();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	tile->Render();
}

void TestScene::PostRender()
{
}

void TestScene::GUIRender()
{
	tile->Edit();
}

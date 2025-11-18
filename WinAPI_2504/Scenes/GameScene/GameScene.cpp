#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	TileManager::Get();
	InstallationManager::Get();
	UIManager::Get();
	Player::Get();

	CAM->SetTarget(nullptr);
}

GameScene::~GameScene()
{
	TileManager::Delete();
	InstallationManager::Delete();
	UIManager::Delete();
	Player::Delete();
}

void GameScene::Update()
{
	//플레이어 매니저랑 날씨 생산 이런거 다 추가해야됨
	switch (UIManager::Get()->GetPanelType())
	{
	case PanelType::BuildPanel:
		UIManager::Get()->Update();
		InstallationManager::Get()->Update();
		TileManager::Get()->Update();
		break;
	case PanelType::CityPanel:
		UIManager::Get()->Update();
		Player::Get()->Update();		
		break;
	}

}

void GameScene::PreRender()
{
}

void GameScene::Render()
{

	switch (UIManager::Get()->GetPanelType())
	{
	case PanelType::BuildPanel:
		TileManager::Get()->Render();
		break;
	case PanelType::CityPanel:

		break;
	}
	InstallationManager::Get()->Render();
}

void GameScene::PostRender()
{
	UIManager::Get()->Render();
}

void GameScene::GUIRender()
{
	TileManager::Get()->Edit();
	Player::Get()->Edit();
}

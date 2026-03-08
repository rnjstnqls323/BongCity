#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	TileManager::Get();
	InstallationManager::Get();
	UIManager::Get();
	Player::Get();

	map = new Map();
	moneyUI = new MoneyAndWeather();
	CAM->SetTarget(nullptr);
}

GameScene::~GameScene()
{
	TileManager::Delete();
	InstallationManager::Delete();
	UIManager::Delete();
	Player::Delete();
	delete map;
	delete moneyUI;
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
	moneyUI->Update();
	map->Update();
}

void GameScene::PreRender()
{
}

void GameScene::Render()
{
	map->Render();
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
	moneyUI->Render();
}

void GameScene::GUIRender()
{
	//TileManager::Get()->Edit();
	Player::Get()->Edit();

	InstallationManager::Get()->Edit();
	map->Edit();

	UIManager::Get()->Edit();

	moneyUI->Edit();
}

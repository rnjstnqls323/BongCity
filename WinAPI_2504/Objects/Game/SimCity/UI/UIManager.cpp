#include "Framework.h"
#include "UIManager.h"

UIManager::UIManager()
{
	CreatePanels();
}

UIManager::~UIManager()
{
	for (int i = 0; i < (int)PanelType::Max; i++)
	{
		delete panels[(PanelType)i];
	}
}

void UIManager::Update()
{
	panels[type]->Update();
}

void UIManager::Render()
{
	panels[type]->Render();
}

void UIManager::Edit()
{
	panels[type]->Edit();
}

void UIManager::CreatePanels()
{
	CreatePanel<CityPanel>(PanelType::CityPanel);
	CreatePanel<BuildPanel>(PanelType::BuildPanel);
}

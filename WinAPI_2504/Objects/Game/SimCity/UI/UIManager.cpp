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
	isMouseOnPanel = false;
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

void UIManager::Reset()
{
	ResetData();
	mode = Mode::None;
	panels[type]->Reset();
}

void UIManager::SetChoiceData(int key)
{
	if (key == InstallationData().key)
	{
		ResetData();
		return;
	}
	choiceData = DataManager::Get()->GetInstallationData(key);
}

void UIManager::CreatePanels()
{
	CreatePanel<CityPanel>(PanelType::CityPanel);
	CreatePanel<BuildPanel>(PanelType::BuildPanel);
}

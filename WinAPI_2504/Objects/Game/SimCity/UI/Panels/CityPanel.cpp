#include "Framework.h"

CityPanel::CityPanel():Panel(PanelType::CityPanel)
{
	Init();
}

CityPanel::~CityPanel()
{
}

void CityPanel::CreateButtons()
{
	CreateButton<Button>(L"CityPanel/BuildButton", Vector3{ 90,500,0 },Vector2{120,60});
}

void CityPanel::SetButtonEvents()
{
	//이벤트 셋팅어케하나보기
	buttons[0]->SetEvent([this]() { ClickBuildButton(); });
}

void CityPanel::ClickBuildButton()
{
	//UImanager에서 화면모드 build로 넘기기
	UIManager::Get()->ChangePanel(PanelType::BuildPanel);
	CAM->SetTarget(buttons[0]);
}

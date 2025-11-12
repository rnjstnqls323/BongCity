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
	CreateButton(L"Test", Vector3{ 0,0,0 },Vector2{1,1});
}

void CityPanel::SetButtonEvents()
{
	//이벤트 셋팅어케하나보기
	//buttons[0]->SetE
}

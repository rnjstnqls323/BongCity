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
	CreateButton<Button>(L"Buttons/x1", Vector3{ 80,430,0 },Vector2{100,50});
}

void CityPanel::SetButtonEvents()
{
	//이벤트 셋팅어케하나보기
	buttons[0]->SetEvent([this]() { ClickBuildButton(); });
	buttons[1]->SetEvent([this]() { ClickSetSpeedValue(); });
}

void CityPanel::ClickBuildButton()
{
	//UImanager에서 화면모드 build로 넘기기
	UIManager::Get()->ChangePanel(PanelType::BuildPanel);
	CAM->SetTarget(buttons[0]);
}

void CityPanel::ClickSetSpeedValue()
{
	float value = Player::Get()->GetSpeedValue();

	if (value == 1.0f)
	{
		Player::Get()->SetSpeedValue(0.5f);
		buttons[1]->GetQuad()->GetMaterial()->SetDiffuseMap(path + L"x2.png");
		//사진바꾸기
	}
	else if (value == 0.5f)
	{
		Player::Get()->SetSpeedValue(0.25f);
		buttons[1]->GetQuad()->GetMaterial()->SetDiffuseMap(path + L"x4.png");
		//사진바꾸기
	}
	else if (value == 0.25f)
	{
		Player::Get()->SetSpeedValue(0.1f);
		buttons[1]->GetQuad()->GetMaterial()->SetDiffuseMap(path + L"x10.png");
		//사진바꾸기
	}
	else
	{
		Player::Get()->SetSpeedValue(1.0f);
		buttons[1]->GetQuad()->GetMaterial()->SetDiffuseMap(path + L"x1.png");
	}
}

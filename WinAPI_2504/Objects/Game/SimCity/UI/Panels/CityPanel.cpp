#include "Framework.h"

CityPanel::CityPanel():Panel(PanelType::CityPanel)
{
	Init();
	CreatePanels();
	transform = new Transform;

}

CityPanel::~CityPanel()
{
}

void CityPanel::Render()
{
	//dayPanel->Render();
	Panel::Render();
}

void CityPanel::Update()
{
	dayPanel->UpdateWorld();
	Panel::Update();
	transform->UpdateWorld();
}

void CityPanel::Edit()
{
	RenderTexture();
	//dayPanel->Edit();
	Panel::Edit();
	transform->Edit();
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

void CityPanel::CreatePanels()
{
	dayPanel = new Quad(L"Resources/Textures/Simcity/UI/Background/panel1.png");
	dayPanel->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
	dayPanel->SetLocalPosition(250, 660, 0);
	dayPanel->SetLocalScale(1, 0.2f, 1);
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

	EventManager::Get()->ExcuteEvent("ChangeSpeed", nullptr);
}

void CityPanel::RenderTexture()
{

	// ImDrawList* drawList = ImGui::GetForegroundDrawList();
	// 
	// string text = "Season : ";
	// switch (Player::Get()->GetSeason())
	// {
	// case Season::Spring:
	// 	text += "Spring \t";
	// 	break;
	// case Season::Summer:
	// 	text += "Summer \t";
	// 	break;
	// case Season::Autumn:
	// 	text += "Autumn \t";
	// 	break;
	// case Season::Winter:
	// 	text += "Winter \t";
	// 	break;
	// }
	// text += "Citizen [" + to_string(Player::Get()->GetResources(Resources::Citizen)) + "]\n";
	// 
	// text += "Day : " + to_string( Player::Get()->GetDay()) + " | Time [ " + to_string(Player::Get()->GetHour()) +
	// 	" : " + to_string(Player::Get()->GetMinute()) + "]\n";
	// text += "Money : " + to_string(Player::Get()->GetResources(Resources::Money))+" | Oil : " 
	// 	+ to_string(Player::Get()->GetResources(Resources::Oil)) +" | Electric : " + to_string(Player::Get()->GetResources(Resources::Electric)) 
	// 	+ " | Iron : " + to_string(Player::Get()->GetResources(Resources::Iron)) +"\n";
	// text += "Congestion [ " + to_string(Player::Get()->GetResources(Resources::Congestion)) + " ]\tEnvironment [ "
	// 	+ to_string(Player::Get()->GetResources(Resources::Environment)) + " ]";
	// 
	// 
	// drawList->AddText(ImVec2(37, SCREEN_HEIGHT - 690), IM_COL32(255, 255, 0, 255), text.c_str());

}

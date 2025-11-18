#include "Framework.h"

BuildPanel::BuildPanel():Panel(PanelType::BuildPanel)
{
	Init();
	panel = new BuildButtonPanel();
	SetEvent();
}

BuildPanel::~BuildPanel()
{
}

void BuildPanel::Update()
{
	panel->Update();
	for (Button* button : buttons)
	{
		button->Update();
		button->UpdateTransform();
	}
}

void BuildPanel::Render()
{
	panel->Render();
	for (Button* button : buttons)
	{
		button->Render();
	}
}

void BuildPanel::Edit()
{
	panel->Edit();
	for (Button* button : buttons)
	{
		button->Edit();
	}
}

void BuildPanel::CreateButtons()
{
	modeButton = CreateButton<Button>(L"Buttons/mode", Vector3{ 70,590,0 }, Vector2{ 120,60 });
	CreateButton<Button>(L"Buttons/removemode", Vector3{ 60,270,0 }, Vector2{ 100,50 });
	CreateButton<Button>(L"Buttons/back", Vector3{ 70,660,0 }, Vector2{ 120,60 });
}

void BuildPanel::SetButtonEvents()
{
	modeButton->SetEvent([this] {ClickModeButton();});
	buttons[1]->SetEvent([this] {ChangeMode(&this->remove); });
	buttons[2]->SetEvent([this] {ClickBackButton(); });
}

void BuildPanel::SetEvent()
{
	EventManager::Get()->AddEvent("ChangeMode", [this](void* param) {ChangeMode((Mode*)param); });
}

void BuildPanel::ClickModeButton()
{
	Mode mode = UIManager::Get()->GetMode();
	switch (mode)
	{
	case Mode::None:
		modeButton->GetQuad()->GetMaterial()->SetDiffuseMap(path + L"buildmode.png");
		UIManager::Get()->SetMode(Mode::Build);
		break;
	case Mode::Build:
		modeButton->GetQuad()->GetMaterial()->SetDiffuseMap(path + L"removemode.png");
		UIManager::Get()->SetMode(Mode::Remove);
		break;
	case Mode::Remove:
		modeButton->GetQuad()->GetMaterial()->SetDiffuseMap(path + L"mode.png");
		UIManager::Get()->SetMode(Mode::None);
		break;
	}
}

void BuildPanel::ClickBackButton()
{
	UIManager::Get()->ChangePanel(PanelType::CityPanel);
	UIManager::Get()->Reset();
	CAM->SetTarget(nullptr);
}

void BuildPanel::ChangeMode(Mode* mode)
{
	switch (*mode)
	{
	case Mode::None:
		modeButton->GetQuad()->GetMaterial()->SetDiffuseMap(path + L"mode.png");
		UIManager::Get()->SetMode(Mode::None);
		break;
	case Mode::Build:
		modeButton->GetQuad()->GetMaterial()->SetDiffuseMap(path + L"buildmode.png");
		UIManager::Get()->SetMode(Mode::Build);
		break;
	case Mode::Remove:
		modeButton->GetQuad()->GetMaterial()->SetDiffuseMap(path + L"removemode.png");
		UIManager::Get()->SetMode(Mode::Remove);
		break;
	}
}

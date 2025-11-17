#include "Framework.h"

BuildButtonPanel::BuildButtonPanel():Panel(PanelType::Max)
{
	Init();
}

BuildButtonPanel::~BuildButtonPanel()
{
	delete collider;
}

void BuildButtonPanel::Update()
{
	if (collider->IsPointCollision(mousePos))
		UIManager::Get()->SetMouseOnPanel(true); //여기 UIManager로 넘겨야됨

	MoveTransform(scrollButton->UpdateTransform(choiceButtons->size() * BUTTON_SIZE));
	
	for (Button* button : *choiceButtons)
	{
		button->Update();
	}
	for (int i = 0; i <= (int)InstallationType::None; i++)
	{
		typeButtons[(InstallationType)i]->Update();
	}
	if (Input::Get()->IsKeyDown(VK_NUMPAD1))
	{
		choiceType = (InstallationType)((int)choiceType-1);
		SetChoiceButtons();
		scrollButton->SetLocalPosition(scrollButton->GetOriginPos());
		scrollButton->Update();
		UpdateTransform();
	}
	collider->UpdateWorld();
}

void BuildButtonPanel::Render()
{
	backGround->Render();
	switch (choiceType)
	{
	case InstallationType::None:
		Panel::Render();
		break;
	default:
		ShowButtonRender();
		break;
	}
	scrollButton->Render();
	for (int i = 0; i <= (int)InstallationType::None; i++)
	{
		typeButtons[(InstallationType)i]->Render();
	}
}

void BuildButtonPanel::Edit()
{
	scrollButton->Edit();
	typeButtons[InstallationType::Road]->Edit();
	ImGui::Text("%f", buttons[0]->GetLocalPosition().x);

	ImGui::Text("%f,%f", scrollButton->GetOriginPos().x, scrollButton->GetOriginPos().y);
	ImGui::Text("%f,%f", scrollButton->GetLocalPosition().x, scrollButton->GetLocalPosition().y);

	ImGui::Text("%d", UIManager::Get()->GetChoiceData().key);
}

void BuildButtonPanel::CreateButtons()
{
	CreateBackGround();

	vector<int> keys = DataManager::Get()->GetKeys();
	int count = 0;
	for (int key : keys)
	{
		InstallationData data = DataManager::Get()->GetInstallationData(key);
		InstallationButton* button = CreateButton<InstallationButton>(L"Installations/" + Utility::ToWString(data.name),
			Vector3{ (float)count++ * BUTTON_SIZE + 70,(float)BUTTON_SIZE*0.8f,0 }, Vector2{ (float)BUTTON_SIZE,(float)BUTTON_SIZE });
		button->SetData(data);
		button->SetOriginPos(button->GetLocalPosition());

		showButtons[(InstallationType)((key / 100) - 1)].emplace_back(button);
	}

	choiceButtons = &buttons;

	typeButtons.reserve((int)InstallationType::None);
	count = 0;
	for (int i = 0; i <= (int)InstallationType::None; i++)
	{
		TypeChoiceButton* button = new TypeChoiceButton(
			L"InstallationType/" + to_wstring(i) + L"_button",
			Vector2{ (float)BUTTON_SIZE, (float)BUTTON_SIZE*0.5f }
		);
		button->SetLocalPosition(Vector3{ (float)count++ * BUTTON_SIZE + 70,210 });
		button->SetType((InstallationType)i);
		button->UpdateTransform();
		typeButtons[(InstallationType)i] = button;
	}
}

void BuildButtonPanel::SetButtonEvents()
{
	vector<int> keys = DataManager::Get()->GetKeys();
	for (int i = 0; i <= (int)InstallationType::None; i++)
	{
		typeButtons[(InstallationType)i]->SetIntParameter(i);
		typeButtons[(InstallationType)i]->SetIntEvent([this](int type) {ClickEventToChoiceTypeButton(type); });
		for (int j = 0; j < showButtons[(InstallationType)i].size(); j++)
		{
			InstallationButton* button = (InstallationButton*)showButtons[(InstallationType)i][j];
			int key = button->GetData().key;
			button->SetIntParameter(key);
			button->SetIntEvent([this, key](int)	{ClickEventToShowButton(key);});
		
		}
	}


}

void BuildButtonPanel::ClickEventToShowButton(int key)
{
	//UIManager 에 버튼 눌린 키 넘겨서 초이스되게 해줘야됨
	UIManager::Get()->SetChoiceData(key);
}

void BuildButtonPanel::ClickEventToChoiceTypeButton(int type)
{
	choiceType = (InstallationType)type;
	SetChoiceButtons();
	scrollButton->SetLocalPosition(scrollButton->GetOriginPos());
	scrollButton->Update();
	UpdateTransform();
}

void BuildButtonPanel::ShowButtonRender()
{
	for (int i = 0; i < showButtons[choiceType].size(); i++)
	{
		showButtons[choiceType][i]->Render();
	}
}

void BuildButtonPanel::UpdateTransform()
{
	int count = 0;
	for (Button* button : *choiceButtons)
	{
		InstallationButton* btn = (InstallationButton*)button;
		btn->SetLocalPosition(Vector3{ (float)count++ * BUTTON_SIZE + 70 ,(float)BUTTON_SIZE * 0.8f,0 });
		btn->SetOriginPos(button->GetLocalPosition());
		btn->Update();
	}
}

void BuildButtonPanel::SetChoiceButtons()
{
	if (preType == choiceType) return;

	switch (choiceType)
	{
	case InstallationType::None:
		choiceButtons = &buttons;
		break;
	default:
		choiceButtons = &showButtons[choiceType];
		break;
	}
	preType = choiceType;
}

void BuildButtonPanel::MoveTransform(float x)
{
	if (x == 0) return;
	
	for (Button* button : *choiceButtons)
	{
		InstallationButton* btn = (InstallationButton*)button;
		Vector3 pos = btn->GetOriginPos();
		btn->SetLocalPosition(Vector3{ pos.x - x, pos.y, pos.z });
	}
}


void BuildButtonPanel::CreateBackGround()
{
	backGround = new Quad(Vector2{ 1500,180 });
	backGround->GetMaterial()->SetDiffuseMap(L"Resources/Textures/Simcity/UI/BackGround/BuildingBackGround.png");
	backGround->SetLocalPosition(Vector3{ 600,90,0 });
	backGround->UpdateWorld();


	scrollButton = new ScrollButton(L"ScrollButton", Vector2{ 100,25 });
	scrollButton->SetLocalPosition(Vector3{ 60,12,0 });
	scrollButton->SetOriginPos(Vector3{ 60,12,0 });
	scrollButton->Update();

	collider = new BoxCollider(Vector3{ backGround->GetSize().x, backGround->GetSize().y,0 });
	collider->SetLocalPosition(backGround->GetLocalPosition());
}

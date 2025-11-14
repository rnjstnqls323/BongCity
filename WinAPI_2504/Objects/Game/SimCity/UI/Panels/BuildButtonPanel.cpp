#include "Framework.h"

BuildButtonPanel::BuildButtonPanel():Panel(PanelType::Max)
{
	Init();
}

BuildButtonPanel::~BuildButtonPanel()
{
}

void BuildButtonPanel::Update()
{
	MoveTransform(scrollButton->Update(choiceButtons->size() * BUTTON_SIZE));
	
	for (Button* button : *choiceButtons)
	{
		button->Update();
	}
	if (Input::Get()->IsKeyDown(VK_NUMPAD1))
	{
		choiceType = (InstallationType)((int)choiceType-1);
		SetChoiceButtons();
		scrollButton->SetLocalPosition(scrollButton->GetOriginPos());
		scrollButton->Update();
		UpdateTransform();
	}

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
}

void BuildButtonPanel::Edit()
{
	scrollButton->Edit();
	ImGui::Text("%f", buttons[0]->GetLocalPosition().x);

	ImGui::Text("%f,%f", scrollButton->GetOriginPos().x, scrollButton->GetOriginPos().y);
	ImGui::Text("%f,%f", scrollButton->GetLocalPosition().x, scrollButton->GetLocalPosition().y);
}

void BuildButtonPanel::CreateButtons()
{
	CreateBackGround();

	vector<int> keys = DataManager::Get()->GetKeys();
	int count = 0;
	for (int key : keys)
	{
		InstallationData data = DataManager::Get()->GetInstallationData(key);
		InstallationButton* button = CreateInstallationButton(L"Installations/" + Utility::ToWString(data.name),
			Vector3{ (float)count++ * BUTTON_SIZE + 70,(float)BUTTON_SIZE*0.8f,0 }, Vector2{ (float)BUTTON_SIZE,(float)BUTTON_SIZE });
		button->SetData(data);
		button->SetOriginPos(button->GetLocalPosition());

		showButtons[(InstallationType)((key / 100) - 1)].emplace_back(button);
	}

	choiceButtons = &buttons;
}

void BuildButtonPanel::SetButtonEvents()
{
}

void BuildButtonPanel::ClickEventToShowButton(int key)
{
	//UIManager 에 버튼 눌린 키 넘겨서 초이스되게 해줘야됨
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
		button->SetLocalPosition(Vector3{ (float)count++ * BUTTON_SIZE + 70 ,(float)BUTTON_SIZE * 0.8f,0 });
		button->SetOriginPos(button->GetLocalPosition());
		button->Update();
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
		Vector3 pos = button->GetOriginPos();
		button->SetLocalPosition(Vector3{ pos.x - x, pos.y, pos.z });
	}
}


void BuildButtonPanel::CreateBackGround()
{
	backGround = new Quad(Vector2{ 1500,180 });
	backGround->GetMaterial()->SetDiffuseMap(L"Resources/Textures/Simcity/UI/BackGround/BuildingBackGround.png");
	backGround->SetLocalPosition(Vector3{ 600,90,0 });
	backGround->UpdateWorld();


	scrollButton = new ScrollButton(L"ScrollButton", Vector2{ 100,20 });
	scrollButton->SetLocalPosition(Vector3{ 60,10,0 });
	scrollButton->SetOriginPos(Vector3{ 60,10,0 });
	scrollButton->Update();

}

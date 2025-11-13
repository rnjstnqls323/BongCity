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
	backGround->UpdateWorld();
	float x;
	switch (choiceType)
	{
	case InstallationType::None:
		x = scrollButton->Update(buttons.size() * BUTTON_SIZE);
		MoveTransformToNone(x);
		break;
	default:
		x = scrollButton->Update(showButtons[choiceType].size() * BUTTON_SIZE);
		MoveTransformToType(x);
		break;
	}
	for (Button* button : buttons)
	{
		button->Update();
	}
	if (Input::Get()->IsKeyDown(VK_NUMPAD1))
	{
		choiceType = (InstallationType)((int)choiceType-1);
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
}

void BuildButtonPanel::CreateButtons()
{
	CreateBackGround();

	vector<int> keys = DataManager::Get()->GetKeys();
	int count = 0;
	for (int key : keys)
	{
		InstallationData data = DataManager::Get()->GetInstallationData(key);
		Button* button = CreateButton(L"Installations/" + Utility::ToWString(data.name),
			Vector3{ (float)count++ * BUTTON_SIZE + 70,(float)BUTTON_SIZE*0.8f,0 }, Vector2{ (float)BUTTON_SIZE,(float)BUTTON_SIZE });
		button->SetData(data);

		//originpos

		showButtons[(InstallationType)((key / 100) - 1)].emplace_back(button);
	}
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
	switch (choiceType)
	{
	case InstallationType::None:
		ChangeTransformToNone();
		break;
	default:
		ChangeTransformToType();
		break;
	}
}

void BuildButtonPanel::ChangeTransformToNone()
{
	//이거 어케 할지 바꿔야되긴함

	int count = 0;
	for (Button* button : buttons)
	{
		button->SetLocalPosition(Vector3{ (float)count++ * BUTTON_SIZE + 70,(float)BUTTON_SIZE * 0.8f,0 });
		button->Update();
	}
	//originpos
}

void BuildButtonPanel::ChangeTransformToType()
{
	int count = 0;
	for (Button* button : showButtons[choiceType])
	{
		button->SetLocalPosition(Vector3{ (float)count++ * BUTTON_SIZE + 70 ,(float)BUTTON_SIZE * 0.8f,0 });
		button->Update();
	}
	//originpos
}

void BuildButtonPanel::MoveTransformToType(float x)
{
	if (x == 0) return;
	for (Button* button : showButtons[choiceType])
	{
		button->SetLocalPosition(Vector3{ button->GetLocalPosition().x - x, button->GetLocalPosition().y,0});
		button->Update();
	}
}

void BuildButtonPanel::MoveTransformToNone(float x)
{
	if (x == 0) return;
	for (Button* button : buttons)
	{
		button->SetLocalPosition(Vector3{ button->GetLocalPosition().x - x, button->GetLocalPosition().y,0 });
		button->Update();
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

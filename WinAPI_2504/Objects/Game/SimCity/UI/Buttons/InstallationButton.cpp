#include "Framework.h"

InstallationButton::InstallationButton(wstring imagePath, Vector2 size):Button(imagePath,size)
{
}

InstallationButton::~InstallationButton()
{
}

void InstallationButton::Update()
{
	if (IsPointCollision(mousePos))
	{
		SetLocalScale(1.2, 1.2, 1);
		GetMaterial()->SetColor(1, 0, 0);
		if (Input::Get()->IsKeyDown(VK_LBUTTON))
		{
			Mode mode = Mode::Build;
			OnClick();
			EventManager::Get()->ExcuteEvent("ChangeMode", &mode);
		}
	}
	else if (UIManager::Get()->GetChoiceData().key == data.key && UIManager::Get()->GetMode() == Mode::Build)
	{
		SetLocalScale(1.2, 1.2, 1);
	}
	else
	{
		GetMaterial()->SetColor(0, 1, 0);
		SetLocalScale(1, 1, 1);
	}
		
	UpdateTransform();
}

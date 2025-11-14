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
			OnClick(); //이벤트 어떤식으로 발생시키더라? 일단 온클릭해놓고 찾아오자
	}
	else
	{
		GetMaterial()->SetColor(0, 1, 0);
		SetLocalScale(1, 1, 1);
	}
		
	UpdateWorld();
	quad->UpdateWorld();
}

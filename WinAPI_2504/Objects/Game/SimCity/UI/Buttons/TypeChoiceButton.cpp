#include "Framework.h"

TypeChoiceButton::TypeChoiceButton(wstring fileName, Vector2 size):Button(fileName, size)
{
}

TypeChoiceButton::~TypeChoiceButton()
{
}

void TypeChoiceButton::Update()
{
	if (IsPointCollision(mousePos))
	{
		GetMaterial()->SetColor(1, 0, 0);
		UIManager::Get()->SetMouseOnPanel(true); //여기 UIManager로 넘겨야됨
		if (Input::Get()->IsKeyDown(VK_LBUTTON))
		{
			Mode mode = Mode::None;
			OnClick(); //이벤트 어떤식으로 발생시키더라? 일단 온클릭해놓고 찾아오자
			EventManager::Get()->ExcuteEvent("ChangeMode", &mode);
		}
	}
	else
	{
		GetMaterial()->SetColor(0, 1, 0);
	}
}


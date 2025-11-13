#include "Framework.h"

ScrollButton::ScrollButton(wstring imagePath, Vector2 size):Button(imagePath, size)
{
}

ScrollButton::~ScrollButton()
{
}

float ScrollButton::Update(int size)
{
	if (Input::Get()->IsKeyPress(VK_LBUTTON) && IsPointCollision(mousePos)&&size>SCREEN_WIDTH)
		isMove = true;
	else if (Input::Get()->IsKeyUp(VK_LBUTTON) && isMove)
		isMove = false;

    if (isMove)
    {
        float x = mousePos.x;
        x = max(60.0f, min(x, SCREEN_WIDTH - GetSize().x * 0.5f));

        SetLocalPosition(Vector3{ x, localPosition.y, 0 });
        UpdateWorld();
        quad->UpdateWorld();

        if (prePos != localPosition)
        {
            float moveX = localPosition.x-originPos.x;

            float temp = size/(float)SCREEN_WIDTH;

            prePos = localPosition;
            xPos = moveX * temp;
            return moveX * temp;
        }
    }
	return 0;
}

void ScrollButton::Edit()
{
    ImGui::Text("%f", xPos);
}

void ScrollButton::Reset()
{
    localPosition = originPos;
    prePos = originPos;
}




#include "Framework.h"

ScrollButton::ScrollButton(wstring imagePath, Vector2 size):Button(imagePath, size)
{
}

ScrollButton::~ScrollButton()
{
}

float ScrollButton::Update(int size)
{
    if (Input::Get()->IsKeyPress(VK_LBUTTON) && IsPointCollision(mousePos) && size > SCREEN_WIDTH)
        isMove = true;
    else if (Input::Get()->IsKeyUp(VK_LBUTTON))
        isMove = false;

    if (isMove)
    {
        float minX = 60.0f;
        float maxX = SCREEN_WIDTH - GetSize().x * 0.5f;

        float x = max(minX, min(mousePos.x, maxX));
        SetLocalPosition(Vector3{ x, localPosition.y, 0 });
        UpdateWorld();
        quad->UpdateWorld();

        // 스크롤바 절대 위치 기준으로 콘텐츠 이동 계산
        float scrollRange = maxX - minX;
        float contentRange = size - SCREEN_WIDTH;
        float xPos = (x - minX) * contentRange / scrollRange;

        prePos = localPosition; // 증분 계산용
        return xPos;            // 절대 이동값
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




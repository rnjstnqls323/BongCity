#include "Framework.h"

Button::Button(wstring fileName)
{
	wstring path = L"Resources/Textures/Simcity/UI/" + fileName + L".png";
	quad = new Quad(Vector2(50,50));
	
	quad->GetMaterial()->SetDiffuseMap(path);

	quad->SetParent(this);

	UpdateWorld();
	quad->UpdateWorld();
}

Button::Button(wstring imagePath, Vector2 size) : BoxCollider(Vector3{ size.x,size.y,1 })
{
	wstring path = L"Resources/Textures/Simcity/UI/" + imagePath + L".png";
	quad = new Quad(size);
	quad->GetMaterial()->SetDiffuseMap(path);
	
	quad->SetParent(this);
	UpdateWorld();
	quad->UpdateWorld();

}

Button::~Button()
{
	delete quad;
}

void Button::Update()
{
	if (IsPointCollision(mousePos))
	{
		GetMaterial()->SetColor(1, 0, 0);
		UIManager::Get()->SetMouseOnPanel(true); //여기 UIManager로 넘겨야됨
		if (Input::Get()->IsKeyDown(VK_LBUTTON))
			OnClick(); //이벤트 어떤식으로 발생시키더라? 일단 온클릭해놓고 찾아오자
	}
	else
	{
		GetMaterial()->SetColor(0, 1, 0);
	}
}

void Button::Render()
{
	BoxCollider::Render();
	quad->Render();
}

void Button::UpdateTransform()
{
	UpdateWorld();
	quad->UpdateWorld();
}

void Button::OnClick()
{
	if (onClick)
		onClick();
	else if (onClickInt)
		onClickInt(intParameter);
	else if (onClickObject)
		onClickObject(objectParameter);
}

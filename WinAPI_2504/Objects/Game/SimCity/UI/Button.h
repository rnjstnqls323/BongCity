#pragma once

class Button : public BoxCollider
{
public:
	Button(wstring fileName);
	Button(wstring imagePath, Vector2 size);
	~Button();
	//생성시 ex) Installation/Data.name 이런식으로 경로하나 더 써주기

	virtual void Update();
	virtual void Render();

	void SetEvent(function<void()> onClick) { this->onClick = onClick; }
	void SetIntEvent(function<void(int)> onClickInt) { this->onClickInt = onClickInt; }
	void SetIntParameter(int intParameter) { this->intParameter = intParameter; }
	void SetObjectEvent(function<void(void*)> onClickObject) { this->onClickObject = onClickObject; }
	void SetObjectParameter(void* objectParameter) { this->objectParameter = objectParameter; }


protected:
	virtual void OnClick();

protected:
	int intParameter = 0;
	void* objectParameter = nullptr;

	function<void()> onClick = nullptr;
	function<void(int)> onClickInt = nullptr;
	function<void(void*)> onClickObject = nullptr;
	Quad* quad;
};
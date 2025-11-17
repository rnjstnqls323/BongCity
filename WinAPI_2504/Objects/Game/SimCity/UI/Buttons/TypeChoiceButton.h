#pragma once

class TypeChoiceButton : public Button
{
public:
	TypeChoiceButton(wstring fileName,Vector2 size);
	~TypeChoiceButton();

	void SetType(InstallationType type) { this->type = type; }
	InstallationType& GetType() { return type; }

private:
	InstallationType type;

};
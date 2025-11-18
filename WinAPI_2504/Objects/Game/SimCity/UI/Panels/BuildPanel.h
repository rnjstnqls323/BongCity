#pragma once

enum class Mode
{
	None, Build, Remove
};
class BuildPanel :public Panel
{
public:
	BuildPanel();
	~BuildPanel();

	void Update() override;
	void Render() override;
	void Edit() override;
protected:
	void CreateButtons() override;
	void SetButtonEvents() override;

	void SetEvent();

	void ClickModeButton();
	void ClickBackButton();
	void ChangeMode(Mode* mode);

private:
	wstring path = L"Resources/Textures/SimCity/UI/Buttons/";

	Mode remove = Mode::Remove;
	BuildButtonPanel* panel;
	Button* modeButton;
};
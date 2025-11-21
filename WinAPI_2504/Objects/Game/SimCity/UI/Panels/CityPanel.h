#pragma once

class CityPanel : public Panel
{
public:
	CityPanel();
	~CityPanel();
	void Reset() override {}

	void Render() override;
	void Update() override;
	void Edit() override;

protected:

	void CreateButtons() override;
	void SetButtonEvents() override;

private:
	void CreatePanels();
	void ClickBuildButton();
	void ClickSetSpeedValue();

	void RenderTexture();

private:
	ImFont* koreanFont;
	Transform* transform;
	wstring path = L"Resources/Textures/Simcity/UI/Buttons/";
	Quad* dayPanel;
};
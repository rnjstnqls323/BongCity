#pragma once

class CityPanel : public Panel
{
public:
	CityPanel();
	~CityPanel();
	void Reset() override {}
protected:

	void CreateButtons() override;
	void SetButtonEvents() override;

private:
	void ClickBuildButton();
	void ClickSetSpeedValue();
private:
	wstring path = L"Resources/Textures/Simcity/UI/Buttons/";
};
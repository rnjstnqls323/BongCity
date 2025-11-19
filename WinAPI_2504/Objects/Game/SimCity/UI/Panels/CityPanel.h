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
};
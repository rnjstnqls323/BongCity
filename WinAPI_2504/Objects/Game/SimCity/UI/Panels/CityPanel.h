#pragma once

class CityPanel : public Panel
{
public:
	CityPanel();
	~CityPanel();

protected:
	void CreateButtons() override;
	void SetButtonEvents() override;

};
#pragma once

enum PanelType
{

};
class Panel
{
public:
	Panel(PanelType type);
	~Panel();

	virtual void Update();
	virtual void Render();

protected:
	virtual void CreateButtons();

protected:
	vector<Button*> buttons;
};
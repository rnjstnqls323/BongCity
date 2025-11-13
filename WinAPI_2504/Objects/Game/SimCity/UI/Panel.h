#pragma once

enum class PanelType
{
	CityPanel, BuildPanel, Max
};

class Panel
{
protected:
	const int MAX_BUTTON_SIZE = 100;
public:
	Panel(PanelType type);
	~Panel();

	virtual void Update();
	virtual void Render();

	PanelType& GetType() { return type; }

	virtual void Edit();
	
protected:
	virtual void CreateButtons() = 0;
	virtual void SetButtonEvents() = 0;
	
	Button* CreateButton(wstring image, Vector3 pos, Vector2 size);
	void Init();
protected:
	PanelType type;
	vector<Button*> buttons;
};
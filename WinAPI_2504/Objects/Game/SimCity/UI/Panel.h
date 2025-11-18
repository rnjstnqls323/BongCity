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
	
	template <typename T>
	T* CreateButton(wstring image, Vector3 pos, Vector2 size)
	{
		T* button = new T(image, size);
		button->SetLocalPosition(pos);
		button->UpdateWorld();
		button->SetTag(Utility::ToString(image));
		button->UpdateTransform();
		buttons.push_back(button);
	
		return button;
	}

	void Init();
protected:
	PanelType type;
	vector<Button*> buttons;
};
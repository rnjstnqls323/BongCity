#pragma once

class UIManager : public Singleton<UIManager>
{
	friend class Singleton<UIManager>;

private:
	UIManager();
	~UIManager();


public:
	void Update();
	void Render();
	void Edit();

	void ChangePanel(PanelType type) { this->type = type; }

private:
	void CreatePanels();
	template <typename T>
	void CreatePanel(PanelType type)
	{
		T* panel = new T;
		panels[type] = panel;
	}

private:
	PanelType type = PanelType::CityPanel;
	unordered_map<PanelType, Panel*> panels;
};
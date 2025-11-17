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
	bool& IsMouseOnPanel() { return isMouseOnPanel; }
	void SetMouseOnPanel(bool isMouseOnPanel) { this->isMouseOnPanel = isMouseOnPanel; }

	void ResetData() { choiceData = InstallationData(); }
	InstallationData& GetChoiceData() { return choiceData; }
	void SetChoiceData(int key);

	bool& IsRemoveMode() { return isRemoveMode; }
	void SetRemoveMode(bool isRemoveMode) { this->isRemoveMode = isRemoveMode; }

private:
	void CreatePanels();
	template <typename T>
	void CreatePanel(PanelType type)
	{
		T* panel = new T;
		panels[type] = panel;
	}

private:
	bool isMouseOnPanel = false;

	bool isRemoveMode = false;

	InstallationData choiceData;
	PanelType type = PanelType::CityPanel;
	unordered_map<PanelType, Panel*> panels;
};
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

	void Reset();
	InstallationData& GetChoiceData() { return choiceData; }
	void SetChoiceData(int key);

	PanelType& GetPanelType(){ return type; }

	void SetMode(Mode mode) { this->mode = mode; }
	Mode GetMode() { return mode; }
	//씬에서 모드보고 넘기기

private:
	void ResetData() { choiceData = InstallationData(); }
	void CreatePanels();
	template <typename T>
	void CreatePanel(PanelType type)
	{
		T* panel = new T;
		panels[type] = panel;
	}

private:
	bool isMouseOnPanel = false;

	Mode mode;

	InstallationData choiceData;
	PanelType type = PanelType::CityPanel;
	unordered_map<PanelType, Panel*> panels;
};
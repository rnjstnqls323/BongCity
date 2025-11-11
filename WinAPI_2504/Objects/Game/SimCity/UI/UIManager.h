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


private:
	void CreatePanels();

private:
	unordered_map<PanelType, Panel*> panels;
};
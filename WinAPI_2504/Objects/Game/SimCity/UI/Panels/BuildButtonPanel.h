#pragma once

class BuildButtonPanel :public Panel
{
private:
	const int BUTTON_SIZE = 120;
public:
	BuildButtonPanel();
	~BuildButtonPanel();

	void Update() override;
	void Render() override;

	void Edit() override;

protected:
	void CreateButtons() override;
	void SetButtonEvents() override;

private:
	void ClickEventToShowButton(int key);
	void ClickEventToChoiceTypeButton(int type);
	
	void ShowButtonRender();
	void UpdateTransform();

	void SetChoiceButtons();

	void MoveTransform(float x);

	void CreateBackGround();


private:
	BoxCollider* collider;
	Quad* backGround;
	ScrollButton* scrollButton;

	InstallationType preType = InstallationType::None;
	InstallationType choiceType = InstallationType::None;

	unordered_map<InstallationType, vector<Button*>> showButtons;
	unordered_map<InstallationType, Button*> typeButtons;
	vector<Button*>* choiceButtons;
};
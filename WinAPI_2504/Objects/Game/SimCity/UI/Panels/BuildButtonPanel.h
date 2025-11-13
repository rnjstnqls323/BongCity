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
	void ShowButtonRender();
	void UpdateTransform();

	void ChangeTransformToNone();
	void ChangeTransformToType();

	void MoveTransformToType(float x);
	void MoveTransformToNone(float x);

	void CreateBackGround();


private:
	Quad* backGround;
	ScrollButton* scrollButton;
	InstallationType choiceType = InstallationType::None;
	unordered_map<InstallationType, vector<Button*>> showButtons;
};
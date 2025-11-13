#pragma once

class BuildPanel :public Panel
{
public:
	BuildPanel();
	~BuildPanel();

	void Update() override;
	void Render() override;
	void Edit() override;
protected:
	void CreateButtons() override;
	void SetButtonEvents() override;

private:
	BuildButtonPanel* panel;

};
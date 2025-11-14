#pragma once

class InstallationButton : public Button
{
public:
	InstallationButton(wstring imagePath, Vector2 size);
	~InstallationButton();

	void Update() override;
	
};
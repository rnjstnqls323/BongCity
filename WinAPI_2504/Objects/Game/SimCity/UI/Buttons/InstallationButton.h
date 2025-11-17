#pragma once

class InstallationButton : public Button
{
public:
	InstallationButton(wstring imagePath, Vector2 size);
	~InstallationButton();

	void Update() override;

	void SetData(InstallationData data) { this->data = data; }
	InstallationData& GetData() { return data; }
	

	void SetOriginPos(Vector3 originPos) { this->originPos = originPos; }
	Vector3& GetOriginPos() { return originPos; }
protected:
	Vector3 originPos;
	InstallationData data;
};
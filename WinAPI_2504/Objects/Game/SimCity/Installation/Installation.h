#pragma once

class Installation : public Transform
{
public:
	Installation();
	~Installation();

	void SetData(const int& key);
	InstallationData& GetData() { return data; }

	virtual void Render();
	virtual void Update();

	void SetSelect(const bool isSelect) { this->isSelect = isSelect; }

	void SetCenterIndex(const Index2& index) { centerIndex = index; }

private:
	void Init();
	virtual void CreateModel() = 0;


private:
	bool isSelect = false;

	InstallationData data;
	Model* model;
	Index2 centerIndex;
};
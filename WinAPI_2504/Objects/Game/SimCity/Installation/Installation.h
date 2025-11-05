#pragma once

class Installation : public Transform
{
public:
	Installation();
	~Installation();

	void SetData(const int& key);
	InstallationData& GetData() { return data; }

	virtual void Render(); //이것도 필요없다
	virtual void Update(); //이거 필요없다

	void SetSelect(const bool isSelect) { this->isSelect = isSelect; }

	void SetCenterIndex(const Index2& index) { centerIndex = index; }

	virtual void Build(const Vector3 pos);
	virtual void Distroy(); //이거 isSelect되고 

private:
	void Init();
	virtual void CreateModel() = 0;


private:
	bool isSelect = false; //이거 기준으로 선택되었으면 계속 업데이트해주기
	bool isBuild = false;

	InstallationData data;
	Index2 centerIndex;
};
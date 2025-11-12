#pragma once

class Installation
{
public:
	Installation();
	~Installation();

	void SetData(const int& key);
	InstallationData& GetData() { return data; }

	Transform* GetTransform() { return transform; }

	Index2& GetCenterIndex() { return centerIndex; }

	//virtual void Update(); //이거 필요없다? 애매띠

	void SetSelect(const bool isSelect) { this->isSelect = isSelect; }
	void SetTransform(Transform* transform) { this->transform = transform; }

	void SetCenterIndex(const Index2& index) { centerIndex = index; }

	virtual void Spawn(const Vector3 pos, int& rotation);
	virtual void Dispawn(); //이거 isSelect되고 


	bool GetIsBuild() { return isBuild; }

private:
	bool isSelect = false; //이거 기준으로 선택되었으면 계속 업데이트해주기
	bool isBuild = false;

	Transform* transform;

	InstallationData data;
	Index2 centerIndex;

	vector<Tile*> sideTiles;
};
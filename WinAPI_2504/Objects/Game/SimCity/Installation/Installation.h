#pragma once

class Installation
{
public:
	Installation();
	~Installation();

	void SetData(const int& key);
	InstallationData& GetData() { return data; }

	Transform* GetTransform() { return transform; }
	Transform* GetFloorTransform() { return floorTransform; }

	Index2& GetCenterIndex() { return centerIndex; }
	InstallationType& GetType() { return type; }

	virtual void Update(); //이거 필요없다? 애매띠 전력쓰는거 체크해야됨

	void SetSelect(const bool isSelect) { this->isSelect = isSelect; }
	void SetTransform(Transform* transform) { this->transform = transform; }
	void SetFloorTransform(Transform* transform) { this->floorTransform = transform; }

	void SetCenterIndex(const Index2& index) { centerIndex = index; }

	virtual void Spawn(const Vector3 pos, int& rotation);
	virtual void Dispawn(); //이거 isSelect되고 


	bool GetIsBuild() { return isBuild; }

protected:
	bool CheckResources();
	virtual void SetType() =0;

protected:
	bool isSelect = false; //이거 기준으로 선택되었으면 계속 업데이트해주기
	bool isBuild = false;

	InstallationType type;

	Transform* transform;
	Transform* floorTransform;

	InstallationData data;
	Index2 centerIndex;

	vector<Tile*> sideTiles;
};
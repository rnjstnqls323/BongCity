#pragma once

enum class InstancingType
{
	None, Possible, Impossible, Max
};
class Tile
{
private:
	const int TILE_SIZE = 150;
public:
	Tile(Index2 index = {0,0});
	~Tile();
	
	void SetInstancingType(const InstancingType& type) { this->instancingType = type; }

	void SetTileType(const InstallationType& type);
	void SetIndex(const Index2& index) { this->index = index; } //이거 필요할까?

	InstallationData& GetData() { return data; }

	InstallationType& GetTileType() { return type; }
	Index2& GetIndex() { return index; }
	Index2& GetCenterIndex() { return center; }
	Vector2 GetSize() { return Vector2{ (float)data.height, (float)data.width }; }
	InstancingType& GetInstancingType() { return instancingType; }	

	void SetTransform(Transform*& transform) { this->transform = transform; }
	Transform*& GetTransform() { return transform; }

	bool IsSideToRoad();

	void SpawnTile(const InstallationType& type, const Index2& centerIndex, InstallationData data);
	void DispawnTile();

private:
	bool isRotation = false;
	InstallationData data = InstallationData();
	Transform* transform; //들고있을 이유있나?
	InstancingType instancingType = InstancingType::None;
	InstallationType type = InstallationType::None;
	Index2 center;
	Index2 index;
};
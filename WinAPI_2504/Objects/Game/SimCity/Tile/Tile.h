#pragma once

enum class InstancingType
{
	None, Possible, Impossible, Max
};
class Tile
{
public:
	Tile(Index2 index = {0,0});
	~Tile();
	
	void SetInstancingType(const InstancingType& type) { this->instancingType = type; }

	void SetTileType(const InstallationType& type);
	void SetIndex(const Index2& index) { this->index = index; } //이거 필요할까?

	InstallationType& GetTileType() { return type; }
	Index2& GetIndex() { return index; }
	InstancingType& GetInstancingType() { return instancingType; }	

	void SetTransform(Transform*& transform) { this->transform = transform; }
	Transform*& GetTransform() { return transform; }

	bool IsSideToRoad();

private:
	Transform* transform; //들고있을 이유있나?
	InstancingType instancingType = InstancingType::None;
	InstallationType type = InstallationType::None;
	Index2 index;
};
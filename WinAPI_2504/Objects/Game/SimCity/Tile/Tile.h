#pragma once

enum class TileType
{
	None, Road, Build, BuildingSide //사이드는 사람들 걸어다니게할거면 이렇게할거임
};
enum class InstancingType
{
	None, Possible, Impossible, Max
};
class Tile : public Transform
{
public:
	Tile(Index2 index = {0,0});
	~Tile();

	void SetInstancingType(const InstancingType& type) { this->instancingType = type; }

	void SetTileType(const TileType& type);
	void SetIndex(const Index2& index) { this->index = index; } //이거 필요할까?

	TileType& GetTileType() { return type; }
	Index2& GetIndex() { return index; }
	InstancingType& GetInstancingType() { return instancingType; }	
private:
	InstancingType instancingType = InstancingType::None;
	TileType type = TileType::None;
	Index2 index;
};
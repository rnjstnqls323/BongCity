#pragma once

enum class TileType
{
	None, Road, Build, BuildingSide //사이드는 사람들 걸어다니게할거면 이렇게할거임
};
class Tile : public RectCollider
{
public:
	Tile(Index2 index = {0,0}, Vector2 size = { 1,1 });
	~Tile();


	void SetTileType(const TileType& type) { this->type = type; }
	void SetIndex(const Index2& index) { this->index = index; } //이거 필요할까?

	TileType& GetTileType() { return type; }
	Index2& GetIndex() { return index; }

private:

	TileType type = TileType::None;
	Index2 index;
};
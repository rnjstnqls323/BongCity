#pragma once

enum class TileType
{
	None, Road, Build, BuildingSide //사이드는 사람들 걸어다니게할거면 이렇게할거임
};
class Tile : public GameObject// 박스 상속받아야되나?
{
public:
	Tile();
	~Tile();

	void Render() override;

	void SetTileType(const TileType& type) { this->type = type; }
	void SetIndex(const Index2& index) { this->index = index; }

	TileType& GetTileType() { return type; }
	Index2& GetIndex() { return index; }

	

private:
	void MakeMesh();

private:
	Vector2 size = { 1,1 };
	Mesh<Vertex>* mesh;
	TileType type;
	Index2 index;
};
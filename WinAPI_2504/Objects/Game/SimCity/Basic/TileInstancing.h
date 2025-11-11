#pragma once

class TileInstancing : public Quad
{
private:
	const int MAX_TILE_SIZE = 100;

private:
	struct InstanceData
	{
		Matrix world;
		Float4 color;

		InstanceData()
		{
			world = XMMatrixIdentity();
			color = Float4(1, 1, 1, 1);
		}
	};
public:
	TileInstancing(wstring path, int size);
	~TileInstancing();


	void UpdateSelectTile(InstallationData* data);

	void UpdateTransform();
	void Render();
	void Edit() override;

	void SetColor(int& index, Float4& color);
	void UpdateInstanceBuffer();

	bool IsPossible() { return isPossible; }

	Index2& GetPreCenter() { return preCenter; }

	vector<class Tile*>& GetPreSelectTiles() { return preSelectTiles; }

	Transform* Add();

private:
	void UpdateSelectTileToBuild();
	void ClearPreTiles();

private:
	class Tile* test;
	bool isPossible;
	int size;
	int drawCount;

	VertexBuffer* instanceBuffer;
	InstanceData* instanceDatas;

	vector<Transform*> transforms;
	vector<class Tile*> preSelectTiles;
	Index2 preCenter;
};
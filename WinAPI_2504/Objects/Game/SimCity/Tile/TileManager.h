#pragma once


class TileManager : public Singleton<TileManager>
{
	friend class Singleton;
private:
	const int TILE_SIZE = 100;
	const int CAMERA_RANGE_HEIGHT = 51;
	const int CAMERA_RANGE_WIDTH = 31;
	
private:
	TileManager();
	~TileManager();

public:
	void Update();
	void Render();
	void RenderInstancing();
	void Edit();
	
	Index2& GetIndexToPos(Vector3& pos);
	Tile* GetTileToIndex(Index2& index);

	void SpawnInstallation(Installation* install);
	

private:
	void CreateInstancing();
	void TileToNearCam();
	void CreateTiles();
	void GetTileToNearMouse(const int& height = 4, const int& width = 7);

private:
	float time = 0.0f;
	int testIndex;
	Tile* hoverTile;
	Index2 real;
	vector<Tile*> tiles;
	unordered_map < InstancingType, pair<QuadInstancing*, vector<Transform*>>> instancing;

	QuadInstancing* tileInstncing;
};
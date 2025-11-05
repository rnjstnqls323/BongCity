#pragma once

class TileManager : public Singleton<TileManager>
{
	friend class Singleton;
private:
	const int TILE_SIZE = 100;
	const int CAMERA_RANGE_HEIGHT = 37;
	const int CAMERA_RANGE_WIDTH = 21;

private:
	TileManager();
	~TileManager();

public:
	void Update();
	void Render();

	
	Index2& GetIndexToPos(Vector3& pos);
	Tile* GetTileToIndex(Index2& index);

	void SpawnInstallation(Installation* install);
	

private:
	void TileToNearCam();
	void CreateTiles();
	vector<Tile*>& GetTileToNearMouse(const int& height = 4, const int& width = 7);

private:
	vector<Tile*> tiles;
	vector<Tile*> nearTiles;
	vector<Tile*> choiceTiles;
};
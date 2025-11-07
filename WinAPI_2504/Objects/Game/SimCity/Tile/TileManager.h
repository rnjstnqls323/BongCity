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
	void Edit();
	
	Index2& GetIndexToPos(Vector3& pos);
	Tile*& GetTileToIndex(Index2& index);

	void SpawnInstallation(Installation* install);
	int GetMaxTileSize() { return TILE_SIZE; }

	Vector3 GetPreCenter() 
	{
		Index2 index = 	tileInstancing->GetPreCenter(); 
		Vector3 pos = { (float)index.col, 0, 100-(float)index.row };
		return pos;
	}

private:

	void CreateTiles();

private:
	vector<Tile*> tiles;

	TileInstancing* tileInstancing;
};
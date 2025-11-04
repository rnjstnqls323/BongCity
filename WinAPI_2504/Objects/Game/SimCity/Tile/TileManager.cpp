#include "Framework.h"

TileManager::TileManager()
{
    CreateTiles();
}

TileManager::~TileManager()
{
    for (Tile* tile : tiles)
        delete tile;
}

void TileManager::Update()
{
    for (Tile* tile : GetTileToNearCam())
    {
        if (!tile->IsActive()) continue;
        tile->SetColor(0, 1, 0);
    }
    //임시
    for (Tile* tile : GetTileToNearMouse())
    {
        if (!tile->IsActive())continue;
        tile->UpdateWorld();
       
        tile->SetColor(1, 0, 0);
    }
}

void TileManager::Render()
{
    for (Tile* tile : GetTileToNearCam())
    {
        if (!tile->IsActive()) continue;
        if (!CAM->ContainPoint(tile->GetGlobalPosition())) continue;
        
        tile->Render();
    }
}

vector<Tile*> TileManager::GetTileToNearCam()
{
    vector<Tile*> nearTiles;

    Index2 ind = { -(int)(CAMERA_RANGE_WIDTH*0.5f)-(int)CAM->GetGlobalPosition().z , (int)CAM->GetGlobalPosition().x };
    int index =0;
    ind.row -= CAMERA_RANGE_WIDTH * 0.5f - 1;
    ind.col -= CAMERA_RANGE_HEIGHT * 0.5f - 1;

    for (int row = 0; row < CAMERA_RANGE_WIDTH; row++)
    {
        for (int col = 0; col < CAMERA_RANGE_HEIGHT; col++)
        {
            Index2 in = { ind.row + row, ind.col + col };
            index = in.ChangeToInt(TILE_SIZE);
            if (index < 0 || index >= TILE_SIZE * TILE_SIZE) continue;

            nearTiles.push_back(tiles[index]);
        }
    }


    return nearTiles;
}


Index2& TileManager::GetIndexToPos(Vector3& pos)
{
    Index2 index = { - (int)pos.z , (int)pos.x };
    return index; //이게 의미가 있을까?
}

Tile* TileManager::GetTileToIndex(Index2& index)
{
    return tiles[index.ChangeToInt(TILE_SIZE)];
}

void TileManager::SpawnInstallation(Installation* install)
{
    GetTileToNearMouse(install->GetData().height, install->GetData().width);
}

void TileManager::CreateTiles()
{
    tiles.reserve(TILE_SIZE * TILE_SIZE);
    for (int row = 0; row < TILE_SIZE; row++)
    {
        for (int col = 0; col < TILE_SIZE; col++)
        {
            Tile* tile = new Tile(Index2(row, col));
            tile->SetLocalPosition(col, 0, -row);


            tile->UpdateWorld();
            tiles.push_back(tile);
        }
    }
}

vector<Tile*> TileManager::GetTileToNearMouse(const int& height, const int& width)
{
    //선택한 건물 사이즈 받아와서 마우스기준 범위처리해서 출력하기
    Ray ray = CAM->ScreenPointToRay(mousePos);
    float t = -ray.origin.y / ray.direction.y;
    Vector3 hitPos = ray.origin + ray.direction * t;
    Index2 ind = { (int)-hitPos.z, (int)hitPos.x };

    vector<Tile*> tile;

    //왼쪽 위 중심잡기 + (중간으로 마우스 위치 보정)
    if (width % 2 == 0)
        ind.row -= (width * 0.5f) - 1;
    else
        ind.row -= width * 0.5f - 1;

    if (height % 2 == 0)
        ind.col -= (height * 0.5f) - 1;
    else
        ind.col -= (height * 0.5f) - 1;

    int index;
    for (int row = 0; row < width; row++)
    {
        for (int col = 0; col < height; col++)
        {
            Index2 in = { ind.row + row, ind.col + col };
            index = in.ChangeToInt(TILE_SIZE);
            if (index < 0 || index >= TILE_SIZE * TILE_SIZE) continue;

            tile.push_back(tiles[index]);
        }
    }

    return tile;
}


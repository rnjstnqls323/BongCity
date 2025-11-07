#include "Framework.h"

TileManager::TileManager()
{
    CreateTiles();
    CreateInstancing();
    hoverTile = new Tile();
}

TileManager::~TileManager()
{
    for (Tile* tile : tiles)
        delete tile;

    for (int i = 0; i < (int)InstancingType::Max; i++)
        delete instancing[(InstancingType)i].first;

    delete hoverTile;
}

void TileManager::Update()
{
    time += DELTA;
    if (time < 0.01f)
        return;
    time -= 0.01f;
    TileToNearCam();

    for (int i = 0; i < (int)InstancingType::Max; i++)
    {
        instancing[(InstancingType)i].first->Update(instancing[(InstancingType)i].second);
    }
    Render();
}

void TileManager::Render()
{
    Environment::Get()->SetAlphaBlend(true);
    for (int i = 0; i < (int)InstancingType::Max; i++)
    {
        instancing[(InstancingType)i].first->Render();
    }
    Environment::Get()->SetAlphaBlend(false);
}

void TileManager::Edit()
{
    if (!hoverTile) return;

    ImGui::Begin("Tile Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Index : (%d, %d)", hoverTile->GetIndex().row, hoverTile->GetIndex().col);
    ImGui::Text("WorldPos : (%.1f, %.1f, %.1f)",
        hoverTile->GetGlobalPosition().x,
        hoverTile->GetGlobalPosition().y,
        hoverTile->GetGlobalPosition().z);

    ImGui::Text("TileType : (%d)",
        hoverTile->GetTileType());

    ImGui::Text("InstancingType : (%d)",
        hoverTile->GetInstancingType());

    ImGui::Text("ChangeIndexToInt : (%d)",
        hoverTile->GetIndex().ChangeToInt(TILE_SIZE));

    ImGui::Text("realIndex : (%d),(%d)",
        real.row, real.col);

    ImGui::Text("Test : (%d)",
        testIndex);
    ImGui::Text("instancing size : (%d, %d, %d)",
        instancing[InstancingType::None].second.size(), instancing[InstancingType::Possible].second.size(), instancing[InstancingType::Impossible].second.size());

    ImGui::End();
}

Index2& TileManager::GetIndexToPos(Vector3& pos)
{
    Index2 index = {(int)pos.z , (int)pos.x };
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

void TileManager::CreateInstancing()
{
    wstring path = L"Resources/Textures/Color/";
    int capacity = CAMERA_RANGE_WIDTH * CAMERA_RANGE_HEIGHT;

    instancing[InstancingType::None] = { new QuadInstancing(path+L"black1.png",capacity),vector<Transform*>()};
    instancing[InstancingType::Possible] = { new QuadInstancing(path+L"green1.png",capacity), vector<Transform*>()};
    instancing[InstancingType::Impossible] = { new QuadInstancing(path+L"red1.png",capacity), vector<Transform*>()};

    instancing[InstancingType::None].second.reserve(capacity);
    instancing[InstancingType::Possible].second.reserve(capacity);
    instancing[InstancingType::Impossible].second.reserve(capacity);
}

void TileManager::TileToNearCam()
{
    //vector<Transform*>& transform = instancing[InstancingType::None].second;
    instancing[InstancingType::None].second.clear();
    instancing[InstancingType::Possible].second.clear();
    instancing[InstancingType::Impossible].second.clear();

    GetTileToNearMouse();

    //transform.size();

    Index2 ind = { (int)(CAMERA_RANGE_WIDTH * 2.5) - (int)CAM->GetGlobalPosition().z , (int)CAM->GetGlobalPosition().x };

    int index = 0;
    ind.row -= CAMERA_RANGE_WIDTH * 0.5f - 1;
    ind.col -= CAMERA_RANGE_HEIGHT * 0.5f - 1;

    for (int row = 0; row < CAMERA_RANGE_WIDTH; row++)
    {
        for (int col = 0; col < CAMERA_RANGE_HEIGHT; col++)
        {
            Index2 in = { ind.row + row, ind.col + col };
            if (in.row > TILE_SIZE || in.row<0 || in.col>TILE_SIZE || in.col < 0) continue;
            index = in.ChangeToInt(TILE_SIZE);
            if (index < 0 || index >= TILE_SIZE * TILE_SIZE) continue;

            instancing[tiles[index]->GetInstancingType()].second.push_back(tiles[index]);

             if (tiles[index]->GetInstancingType() == InstancingType::Possible)
                 tiles[index]->SetInstancingType(InstancingType::None);
             else if (tiles[index]->GetInstancingType() == InstancingType::Impossible && tiles[index]->GetTileType() == TileType::None)
                 tiles[index]->SetInstancingType(InstancingType::None);
        }
    }

}

void TileManager::CreateTiles()
{
    tiles.reserve(TILE_SIZE * TILE_SIZE);
    Vector3 startPos = {0.5f, 0, (float)TILE_SIZE - 0.5f };
    for (int row = 0; row < TILE_SIZE; row++)
    {
        for (int col = 0; col < TILE_SIZE; col++)
        {
            Tile* tile = new Tile(Index2(row, col));
            tile->SetLocalPosition(startPos.x + col, 0, startPos.z);
            tile->SetLocalRotation(XMConvertToRadians(90), 0, 0);

            tile->UpdateWorld();
            tiles.push_back(tile);
        }
        startPos.z--;
    }
}

void TileManager::GetTileToNearMouse(const int& height, const int& width)
{
    //선택한 건물 사이즈 받아와서 마우스기준 범위처리해서 출력하기
    Ray ray = CAM->ScreenPointToRay(mousePos);
    float t = -ray.origin.y / ray.direction.y;


    Vector3 hitPos = ray.origin + ray.direction * t;
    Index2 ind = { (int) -(hitPos.z-100), (int)hitPos.x };

    // 맵 범위 체크
    if (ind.row < 0 || ind.col < 0 || ind.row >= TILE_SIZE || ind.col >= TILE_SIZE)
    {
        hoverTile = nullptr; // 밖으로 나가면 hoverTile 비우기
        return;
    }

    real = ind;
    testIndex = ind.ChangeToInt(TILE_SIZE);
    hoverTile = tiles[ind.ChangeToInt(TILE_SIZE)];

    //왼쪽 위 중심잡기 + (중간으로 마우스 위치 보정)
    if (width % 2 == 0)
        ind.row -= (width * 0.5f) - 1;
    else
        ind.row -= width * 0.5f - 1;

    if (height % 2 == 0)
        ind.col -= (height * 0.5f) - 1;
    else
        ind.col -= (height * 0.5f) - 1;

    

    bool isPossible = true;
    int index;
    vector<Tile*> possible;
    possible.reserve(width * height);
    for (int row = 0; row < width; row++)
    {
        for (int col = 0; col < height; col++)
        {
            Index2 in = { ind.row + row, ind.col + col };
            index = in.ChangeToInt(TILE_SIZE);

            if (in.row < 0 || in.col < 0 || in.row >= TILE_SIZE || in.col >= TILE_SIZE)
            {
                isPossible = false;
            }
            else
            {
                possible.push_back(tiles[index]);
                if (tiles[index]->GetTileType() != TileType::None)
                    isPossible = false;
            }
        }
    }
    
    InstancingType type = isPossible ? InstancingType::Possible : InstancingType::Impossible;

    for (Tile* tile : possible)
        tile->SetInstancingType(type);
}


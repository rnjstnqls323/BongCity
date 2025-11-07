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
    int key = 100;
    if (Input::Get()->IsKeyDown(VK_LBUTTON)&& tileInstancing->IsPossible())
    {
        if (!InstallationManager::Get()->SpawnInstallation(key, GetPreCenter(), tileInstancing->GetPreCenter())) return; 

        // 이것도 고른거 데베 받아와서 셋팅해주기
        // 이거 쪼개서 타일위에서 애초에 false면 빨갛게 출력해야겠다 check부분을 ispossible쪽에서
        // 해주면될듯??
        // 
        // + 내가 고른것도 보였으면좋겠는데 계속 월드업데이트해야돼서 좀 부담스러우려나? 아님 꼼수를 써?? 

        for (Tile* tile : tileInstancing->GetPreSelectTiles())
        {
            tile->SetTileType(InstallationType::Road); //이거 데베받아와서 셋팅해주면됨 (선택된 건물알아야겠네)
        }

    }
    tileInstancing->UpdateSelectTile(DataManager::Get()->GetInstallationData(key).height, DataManager::Get()->GetInstallationData(key).width);//건물 크기 넘겨줘야됨
}

void TileManager::Render()
{
    tileInstancing->Render();
}


void TileManager::Edit()
{
   
}

Index2& TileManager::GetIndexToPos(Vector3& pos)
{
    Index2 index = {(int)pos.z , (int)pos.x };
    return index; //이게 의미가 있을까?
}

Tile*& TileManager::GetTileToIndex(Index2& index)
{
    return tiles[index.ChangeToInt(TILE_SIZE)];
}

void TileManager::SpawnInstallation(Installation* install)
{
   
}

void TileManager::CreateTiles()
{
	tileInstancing = new TileInstancing(L"Resources/Textures/Color/black1.png", TILE_SIZE * TILE_SIZE);

    tiles.reserve(TILE_SIZE * TILE_SIZE);
    Vector3 startPos = {0.5f, 0, (float)TILE_SIZE - 0.5f };
    for (int row = 0; row < TILE_SIZE; row++)
    {
        for (int col = 0; col < TILE_SIZE; col++)
        {
            Transform* transform = tileInstancing->Add();
			transform->SetLocalPosition(startPos.x + col, 0, startPos.z);
			transform->SetLocalRotation(XMConvertToRadians(90), 0, 0);

            Tile* tile = new Tile(Index2(row, col));
            tile->SetTransform(transform);
            tiles.push_back(tile);
        }
        startPos.z--;
    }

    tileInstancing->UpdateTransform();
}

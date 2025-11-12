#include "Framework.h"

TileManager::TileManager()
{
    CreateTiles();

    keys = DataManager::Get()->GetKeys();
}

TileManager::~TileManager()
{
    for (Tile* tile : tiles)
        delete tile;
}

void TileManager::Update()
{

    //버튼 클릭하는거 업데이트 제대로 설정해주기
    // 데이터 받아온걸로 셋팅해주는 코드 필요함 (이부분 UI랑 같이하면됨)
    // 데이터 받아온걸로 환경도랑 혼잡도 넣어줘야됨 + 없애면서 환경도 혼잡도 밸류 조정해줘야됨
    //

    //if (Input::Get()->IsKeyDown(VK_RBUTTON))
    //{
    //    if (key == 200)
    //        key = 0;
    //    else
    //        key = 200;
    //}

    if (Input::Get()->IsKeyDown(VK_RBUTTON))
    {
        key++;
    }


    if (key > keys.size())
    {
        data = InstallationData();
        rotation = 0;
    }
    else if (data.key != keys[key] || data.key == InstallationData().key)
    {
        data = DataManager::Get()->GetInstallationDataCopy(keys[key]); //매번 복사생성자 되는데 이것도 선택하면 카피하는걸로 바꿔야겠다
        rotation = 0;
    }
    //-> 이부분 iskeydown이랑 같이 봐야되는데, 이거 ui기준으로 선택할거라 uimanager에서 받아와서 수정해줘야됨

    if (Input::Get()->IsKeyDown('E'))
    {
        int temp = data.width;
        data.width = data.height;
        data.height = temp;
        rotation += 90;
    }

    if (key > keys.size() && Input::Get()->IsKeyDown(VK_LBUTTON)&& // key상수넣는거 빼야됨 UI에서select보고 처리해야됨
        tiles[tileInstancing->GetPreCenter().ChangeToInt(TILE_SIZE)]->GetTileType() !=InstallationType::None)
    {
        InstallationManager::Get()->DispawnInstallation(tiles[tileInstancing->GetPreCenter().ChangeToInt(TILE_SIZE)]->GetData().key,
            tileInstancing->GetPreCenter());
        for (Tile* tile : tileInstancing->GetPreSelectTiles())
        {
            tile->DispawnTile();
        }

        //건물 없애기(삭제)

    }
    else if (Input::Get()->IsKeyDown(VK_LBUTTON)&& tileInstancing->IsPossible())
    {
        InstallationManager::Get()->SpawnInstallation(data, GetPreCenter(), tileInstancing->GetPreCenter(), rotation);

        // 이것도 고른거 데베 받아와서 셋팅해주기

        for (Tile* tile : tileInstancing->GetPreSelectTiles())
        {
            tile->SpawnTile(DataManager::Get()->GetInstallationData(keys[key]).type, tileInstancing->GetPreCenter(), data); //이거 데베받아와서 셋팅해주면됨 (선택된 건물알아야겠네)
        }

    }
    tileInstancing->UpdateSelectTile(&data);//건물 크기 넘겨줘야됨

    InstallationManager::Get()->ShowInstallationToMouse(data, GetPreCenter(), tileInstancing->GetPreCenter(), rotation);
}

void TileManager::Render()
{
    tileInstancing->Render();
}


void TileManager::Edit()
{
    tileInstancing->Edit();
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

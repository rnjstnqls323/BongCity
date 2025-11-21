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

    //버튼 클릭하는거 업데이트 제대로 설정해주기
    // 데이터 받아온걸로 셋팅해주는 코드 필요함 (이부분 UI랑 같이하면됨)
    // 데이터 받아온걸로 환경도랑 혼잡도 넣어줘야됨 + 없애면서 환경도 혼잡도 밸류 조정해줘야됨
    //


    SetChoiceData();
    InstallationRotation();

    //if (Input::Get()->IsKeyDown('P'))
    //    UIManager::Get()->SetRemoveMode(true);
    //else if (Input::Get()->IsKeyDown('O'))
    //    UIManager::Get()->SetRemoveMode(false);
    // 
    //삭제모드로 바꾸는거 잘됨 씬으로빼자

    if (UIManager::Get()->GetMode() == Mode::None || UIManager::Get()->IsMouseOnPanel())
    {
        return;
    }
    RemoveInstallation();
    BuildInstallation();

    tileInstancing->UpdateSelectTile(&data);//건물 크기 넘겨줘야됨
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


void TileManager::SetChoiceData()
{

    key = UIManager::Get()->GetChoiceData().key;

    if (UIManager::Get()->GetMode() == Mode::Remove)
    {
        data = InstallationData();
        rotation = 0;
    }
    else if (data.key != key)
    {
        data = DataManager::Get()->GetInstallationDataCopy(key);
        rotation = 0;
    }
    //-> 이부분 iskeydown이랑 같이 봐야되는데, 이거 ui기준으로 선택할거라 uimanager에서 받아와서 수정해줘야됨
}

void TileManager::InstallationRotation()
{
    if (Input::Get()->IsKeyDown('E'))
    {
        int temp = data.width;
        data.width = data.height;
        data.height = temp;
        rotation += 90;
    } 
    else if (Input::Get()->IsKeyDown('Q'))
    {
        int temp = data.width;
        data.width = data.height;
        data.height = temp;
        rotation -= 90;
    }
}

void TileManager::BuildInstallation()
{
    if (UIManager::Get()->GetMode() != Mode::Build) return;
    if (Input::Get()->IsKeyDown(VK_LBUTTON) && tileInstancing->IsPossible())
    {
       if(!InstallationManager::Get()->SpawnInstallation(data, GetPreCenter(), tileInstancing->GetPreCenter(), rotation)) return;
        
        // 이것도 고른거 데베 받아와서 셋팅해주기

        for (Tile* tile : tileInstancing->GetPreSelectTiles())
        {
            tile->SpawnTile(DataManager::Get()->GetInstallationData(key).type, tileInstancing->GetPreCenter(), data); //이거 데베받아와서 셋팅해주면됨 (선택된 건물알아야겠네)
        }

    }
    InstallationManager::Get()->ShowInstallationToMouse(data, GetPreCenter(), tileInstancing->GetPreCenter(), rotation);
}

void TileManager::RemoveInstallation()
{
    if (UIManager::Get()->GetMode()!=Mode::Remove) return;
    //Index2 index = tileInstancing->GetPreCenter();
    //
    //if (index.row < 0 || index.col < 0 || index.row >= TILE_SIZE || index.col >= TILE_SIZE)return;

    if (Input::Get()->IsKeyDown(VK_LBUTTON) &&
        tileInstancing->IsPossible())
    {
        InstallationManager::Get()->DispawnInstallation(tiles[tileInstancing->GetPreCenter().ChangeToInt(TILE_SIZE)]->GetData().key,
            tileInstancing->GetPreCenter());
        for (Tile* tile : tileInstancing->GetPreSelectTiles())
        {
            tile->DispawnTile();
        }
        //건물 없애기(삭제)
    }
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

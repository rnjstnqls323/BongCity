#include "Framework.h"

TileInstancing::TileInstancing(wstring path, int size):Quad(path, true)
{
	this->size = size;
	//maxTileSize = TileManager::Get()->GetMaxTileSize();

	material->SetShader(L"Instancing/QuadInstancing.hlsl");

	instanceDatas = new InstanceData[size];
	instanceBuffer = new VertexBuffer(instanceDatas, sizeof(InstanceData), size);

	transforms.reserve(MAX_TILE_SIZE * MAX_TILE_SIZE);
	preSelectTiles.reserve(MAX_TILE_SIZE);
}
TileInstancing::~TileInstancing()
{
	delete[] instanceDatas;
	delete instanceBuffer;

	for (Transform* transform : transforms)
	{
		delete transform;
	}
}



void TileInstancing::UpdateSelectTile(InstallationData* data)
{
	ClearPreTiles();

	
	Ray ray = CAM->ScreenPointToRay(mousePos);
	float t = -ray.origin.y / ray.direction.y;

	Vector3 hitPos = ray.origin + ray.direction * t;
	preCenter = { (int)-(hitPos.z - 100), (int)hitPos.x };

	if (preCenter.row < 0 || preCenter.col < 0 || preCenter.row >= MAX_TILE_SIZE || preCenter.col >= MAX_TILE_SIZE)
		return;

	if (data->key == InstallationData().key) //이부분 상수 최대한 안쓰는 방법으로 가야됨 아마 UI매니저에 Select참조해서 처리하면될듯?
	{
		UpdateSelectTileToBuild();
		return;
	}

	test = TileManager::Get()->GetTileToIndex(preCenter);

	//왼쪽 위 중심잡기 + (중간으로 마우스 위치 보정)
	preCenter.row -= (data->width * 0.5f) - 1;
	preCenter.col -= (data->height * 0.5f) - 1;


	int index;
	Index2 in;

	bool isRoad = false;

	for (int row = 0; row < data->width; row++)
	{
		for (int col = 0; col < data->height; col++)
		{
			in = { preCenter.row + row, preCenter.col + col };

			if (in.row < 0 || in.col < 0 || in.row >= MAX_TILE_SIZE || in.col >= MAX_TILE_SIZE
				|| TileManager::Get()->GetTileToIndex(in)->GetTileType() != InstallationType::None)
			{
				isPossible = false;
				break;
			}
			if (isRoad) continue;
			else if (data->type == InstallationType::Road || TileManager::Get()->GetTileToIndex(in)->IsSideToRoad())
				isRoad = true;
		}
		if (!isPossible)
			break;
	}
	if (!isRoad)
		isPossible = false;
	for (int row = 0; row < data->width; row++)
	{
		for (int col = 0; col < data->height; col++)
		{
			in = { preCenter.row + row, preCenter.col + col };

			index = in.ChangeToInt(MAX_TILE_SIZE);
			if (in.row < 0 || in.col < 0 || in.row >= MAX_TILE_SIZE || in.col >= MAX_TILE_SIZE)
				continue;
			if (!isPossible)
			{
				instanceDatas[index].color = Float4(1, 0, 0, 1);
			}
			else
			{
				instanceDatas[index].color = Float4(0, 1, 0, 1);
			}
			preSelectTiles.push_back(TileManager::Get()->GetTileToIndex(in));
		}
	}

	instanceBuffer->Update(instanceDatas, size);
}

void TileInstancing::UpdateTransform()
{
	drawCount = 0;
	for (Transform* t : transforms)
	{		
		t->UpdateWorld();
		instanceDatas[drawCount].world = XMMatrixTranspose(t->GetWorld());
		drawCount++;
	}
	instanceBuffer->Update(instanceDatas, drawCount);
}

void TileInstancing::Render()
{
	Environment::Get()->SetAlphaBlend(true);
	instanceBuffer->Set(1);
	GetMaterial()->Set();
	mesh->DrawInstanced(size);
	Environment::Get()->SetAlphaBlend(false);
}

void TileInstancing::Edit()
{
	ImGui::Text("Tile Type: %d", test->GetTileType());
}

void TileInstancing::SetColor(int& index, Float4& color)
{ 
	//이거 다하면 인스턴스 버퍼 업데이트 해줘야됨
	instanceDatas[index].color = color;
}

void TileInstancing::UpdateInstanceBuffer()
{
	instanceBuffer->Update(instanceDatas, drawCount);
}

Transform* TileInstancing::Add()
{
	Transform* transform = new Transform;
	transforms.push_back(transform);
	return transform;
}

void TileInstancing::UpdateSelectTileToBuild()
{
	int index = preCenter.ChangeToInt(MAX_TILE_SIZE);
	Index2 in;
	if (TileManager::Get()->GetTileToIndex(preCenter)->GetTileType() != InstallationType::None)
	{
		Vector2 size = TileManager::Get()->GetTileToIndex(preCenter)->GetSize();

		preCenter = TileManager::Get()->GetTileToIndex(preCenter)->GetCenterIndex();

		preCenter.row -= (size.y * 0.5f) -2;
		preCenter.col -= (size.x * 0.5f) - 2;

		for (int row = 0; row < size.y; row++)
		{
			for (int col = 0; col < size.x; col++)
			{
				in = Index2{ preCenter.row + row, preCenter.col + col };
				index = in.ChangeToInt(MAX_TILE_SIZE);
				instanceDatas[index].color = Float4(1, 1, 0.3, 1);
				preSelectTiles.push_back(TileManager::Get()->GetTileToIndex(in));
			}
		}
	}
	else
	{
		instanceDatas[index].color = Float4(1, 0, 1, 1);
		preSelectTiles.push_back(TileManager::Get()->GetTileToIndex(preCenter));
	}



	isPossible = false;
	instanceBuffer->Update(instanceDatas, size);
}

void TileInstancing::ClearPreTiles()
{
	for (Tile* tile : preSelectTiles)
	{
		int index = tile->GetIndex().ChangeToInt(MAX_TILE_SIZE);
		if (tile->GetTileType() == InstallationType::Building || tile->GetTileType() == InstallationType::Road)
		{
			instanceDatas[index].color = Float4(1, 0.3, 0.5, 1);
		}
		else if (tile->GetTileType() == InstallationType::LandScape)
		{
			instanceDatas[index].color = Float4(0.5, 0.7, 1, 1);
		}
		else
		{
			instanceDatas[index].color = Float4(1, 1, 1, 1);
		}
	}
	preSelectTiles.clear();
	isPossible = true;
}

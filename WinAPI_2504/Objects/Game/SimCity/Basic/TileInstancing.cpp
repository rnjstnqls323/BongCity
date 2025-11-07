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

void TileInstancing::UpdateSelectTile(int height, int width)
{
	ClearPreTiles();

	Ray ray = CAM->ScreenPointToRay(mousePos);
	float t = -ray.origin.y / ray.direction.y;

	Vector3 hitPos = ray.origin + ray.direction * t;
	preCenter = { (int)-(hitPos.z - 100), (int)hitPos.x };

	if (preCenter.row < 0 || preCenter.col < 0 || preCenter.row >= MAX_TILE_SIZE || preCenter.col >= MAX_TILE_SIZE)
		return;

	//왼쪽 위 중심잡기 + (중간으로 마우스 위치 보정)
	preCenter.row -= (width * 0.5f) - 1;
	preCenter.col -= (height * 0.5f) - 1;


	int index;
	Index2 in;

	for (int row = 0; row < width; row++)
	{
		for (int col = 0; col < height; col++)
		{
			in = { preCenter.row + row, preCenter.col + col };

			if (in.row < 0 || in.col < 0 || in.row >= MAX_TILE_SIZE || in.col >= MAX_TILE_SIZE 
				|| TileManager::Get()->GetTileToIndex(in)->GetTileType() != InstallationType::None)
			{
				isPossible = false;
				break;
			}
		}
		if (!isPossible)
			break;
	}
	for (int row = 0; row < width; row++)
	{
		for (int col = 0; col < height; col++)
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

void TileInstancing::ClearPreTiles()
{
	for (Tile* tile : preSelectTiles)
	{
		int index = tile->GetIndex().ChangeToInt(MAX_TILE_SIZE);
		if (tile->GetInstancingType() == InstancingType::Impossible)
		{
			instanceDatas[index].color = Float4(1, 0, 0, 1);
		}
		else
		{
			instanceDatas[index].color = Float4(1, 1, 1, 1);
		}
	}
	preSelectTiles.clear();
	isPossible = true;
}

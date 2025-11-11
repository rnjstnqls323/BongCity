#include "Framework.h"

//Tile::Tile(Vector2 size):RectCollider(size)
//{
//	//SetLocalRotation(XMConvertToRadians(90.0f), 0, 0);
//	UpdateWorld();
//}

Tile::Tile(Index2 index):index(index)
{
}

Tile::~Tile()
{
}

void Tile::SetTileType(const InstallationType& type)
{
	this->type = type;
	if (type == InstallationType::None)
		instancingType = InstancingType::None;
	else
		instancingType = InstancingType::Impossible;
}

bool Tile::IsSideToRoad()
{
	Index2 arr[] = { {1,0},{-1,0},{0,1},{0,-1} };

	for (int i = 0; i < 4; i++)
	{
		if (index + arr[i] < Index2{ 0,0 } || index + arr[i] > Index2{ 100,100 })
			continue;
		Index2 ind = index + arr[i];
		if (TileManager::Get()->GetTileToIndex(ind)->GetTileType() == InstallationType::Road) return true;
	}
	return false;
}

void Tile::SpawnTile(const InstallationType& type, const Index2& centerIndex, InstallationData data)
{
	this->type = type;
	this->center = centerIndex;
	this->data = data;
	instancingType = InstancingType::Impossible;
}

void Tile::DispawnTile()
{
	this->type = InstallationType::None;
	center = Index2{ 0,0 };
	data = InstallationData();
	instancingType = InstancingType::None;
}


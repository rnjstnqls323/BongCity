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


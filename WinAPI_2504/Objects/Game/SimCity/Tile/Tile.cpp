#include "Framework.h"

//Tile::Tile(Vector2 size):RectCollider(size)
//{
//	//SetLocalRotation(XMConvertToRadians(90.0f), 0, 0);
//	UpdateWorld();
//}

Tile::Tile(Index2 index, Vector2 size):RectCollider(size),index(index)
{
}

Tile::~Tile()
{
	delete mesh;
}

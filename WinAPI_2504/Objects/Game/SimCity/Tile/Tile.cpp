#include "Framework.h"

Tile::Tile(Vector2 size):RectCollider(size)
{
	SetLocalRotation(XMConvertToRadians(90.0f), 0, 0);
	UpdateWorld();
}

Tile::~Tile()
{
	delete mesh;
}

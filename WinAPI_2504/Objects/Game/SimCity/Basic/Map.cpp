#include "Framework.h"

Map::Map()
{
	CreatePlane();
	CreatePlane();
	CreateTree();

}

Map::~Map()
{
	delete floor;
	delete trees;
}

void Map::Update()
{

}

void Map::Render()
{
	floor->Render();
	trees->Render();
}

void Map::Edit()
{
	floor->Edit();
}

void Map::CreatePlane()
{
	floor = new Plane(Vector2{ (float)PLANE_SIZE,(float)PLANE_SIZE });
	floor->GetMaterial()->SetDiffuseMap(L"Resources/Textures/SimCity/UI/BackGround/plane4.png");
	floor->SetLocalPosition(Vector3{ TILE_SIZE * 0.5f, -0.05, TILE_SIZE * 0.5f });
	floor->UpdateWorld();
}

void Map::CreateTree()
{
	trees = new Tree(Vector2{ (float)PLANE_SIZE,(float)PLANE_SIZE }, 5000, Vector2{ (float)TILE_SIZE,(float)TILE_SIZE }, floor->GetLocalPosition());
}

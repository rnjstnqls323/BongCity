#include "Framework.h"

Map::Map()
{
	CreatePlane();
	CreateTree();
	CreateSunMoon();
	CreateSkyBox();
}

Map::~Map()
{
	delete floor;
	delete trees;
	delete sky;
}

void Map::Update()
{
	sunMoon->Update();
	sky->Update();
}

void Map::Render()
{
	sky->Render();
	floor->Render();
	//plane->Render();
	trees->Render();
	sunMoon->Render();

}

void Map::Edit()
{
	//floor->Edit();
	sunMoon->Edit();
	sky->Edit();
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

void Map::CreateSunMoon()
{
	sunMoon = new SunMoon();
}

void Map::CreateSkyBox()
{
	sky = new SkyBox(L"Resources/Textures/Landscape/blueSky.dds");
}

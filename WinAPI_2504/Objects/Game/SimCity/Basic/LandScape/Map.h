#pragma once

class Map
{
private:
	const int TILE_SIZE = 150;
	const int PLANE_SIZE = 500;
public:
	Map();
	~Map();

	void Update();
	void Render();

	void Edit();
private:
	void CreatePlane();
	void CreateTree();
	void CreateSunMoon();
	void CreateSkyBox();
private:
	Plane* floor;
	Tree* trees;
	SunMoon* sunMoon;
	SkyBox* sky;
};
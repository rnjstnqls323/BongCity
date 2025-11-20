#pragma once

class SkyBox : public Sphere
{
public:
	SkyBox(wstring textureFile);
	~SkyBox();

	void Render();

private:
	Texture* cubeMap;

	RasterizerState* rasterizerStates[2];
	DepthStencilState* depthStencilStates[2];
};
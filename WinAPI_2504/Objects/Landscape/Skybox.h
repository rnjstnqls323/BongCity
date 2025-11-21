#pragma once

class SkyBox : public Sphere
{
private:
	const float ROTATION_SPEED = 0.001f;
	const float SMOOTH_SPEED = 0.01f;
	const float EPSILON = 0.0001f;
public:
	SkyBox(wstring textureFile);
	~SkyBox();

	void Render();
	void Edit() override;

	void Update();
private:
	void UpdateColor();
	void SetEvent();

	void OriginColor();
	void NightColor();
	void SunsetColor();

	void ChangeSpeed();
private:
	float playSpeed = 1.0f;
	float angle = 0.0f;

	Vector3 color;
	Vector3 sunsetColor = { 213.0f / 255, 163.0f / 255, 138.0f / 255 };
	Vector3 nightColor= { 40.0f / 255, 40.0f / 255, 70.0f / 255 };
	Vector3 originColor = { 1,1,1 };


	Texture* cubeMap;

	SkyBuffer* buffer;
	RasterizerState* rasterizerStates[2];
	DepthStencilState* depthStencilStates[2];
};
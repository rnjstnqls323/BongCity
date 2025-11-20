#pragma once

class SunMoon
{
private:
	const float SMOOTH_VALUE = 0.05;
	const float SMOOTH_COLOR_VALUE = 0.005;
	const float EPSILON = 0.0001f;
public:
	SunMoon();
	~SunMoon();

	void Update();
	void Render();

	void Edit();
private:
	void EditLight(LightBuffer::Light& light);
	void CreateLight();

	void OnSun();
	void OnMoon();

	void MatchSeason();
	void UpdateLight();
	void SunSetEmbient();
	void OriginEmbient();
	
	void SetLiner();

	void AddEvent();
	
private:
	float correct;
	float linear;
	
	Float3 embientColor;
	Float4 nextLightColor;

	SeasonData* data;

	Season season;

	Vector3 originDir = Vector3{ -1,-1,1 };

	LightBuffer* buffer;

	LightBuffer::Light* nowLight;

	LightBuffer::Light* sun;
	LightBuffer::Light* moon;
};
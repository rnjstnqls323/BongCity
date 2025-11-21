#pragma once

class SunMoon
{
private:
	const float SMOOTH_VALUE = 0.05;
	const float SMOOTH_COLOR_VALUE = 0.01;
	const float EPSILON = 0.0001f;
	const float CORRECT_VALUE = 200;
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
	
	void ChangeSpeed();
	
	void SetLiner();

	void AddEvent();
	
private:
	float speed = 1;
	float correct;
	float linear;
	
	Float3 embientColor;
	Float4 nextLightColor;

	SeasonData* data;

	Season season;

	Vector3 originPos = Vector3{ -150,50,100 };

	LightBuffer* buffer;

	LightBuffer::Light* nowLight;

	LightBuffer::Light* sun;
	LightBuffer::Light* moon;
};
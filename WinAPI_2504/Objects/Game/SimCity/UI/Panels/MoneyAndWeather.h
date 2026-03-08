#pragma once

class MoneyAndWeather
{
public:
	MoneyAndWeather();
	~MoneyAndWeather();

	void Update();
	void Render();

	void Edit();
private:
	void CreateQuad();
	void CreateValue();
	void UpdateSeason();

private:
	Season preSeason;

	vector<BasicValue*> values;

	Quad* weatherBackGround;
	Quad* weatherFront;
};
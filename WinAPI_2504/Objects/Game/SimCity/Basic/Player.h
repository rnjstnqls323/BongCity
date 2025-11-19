#pragma once

enum class Resources
{
	Money, Oil, Electric, Iron, Citizen
};


class Player : public Singleton<Player>
{
	friend class Singleton<Player>;
private:
	const int REAL_TIME = 60;
	const int DAY_HOUR = 24;
	const int MAX_SEASON_DAY = 7;
private:
	Player();
	~Player();

public:
	void Add(Resources resources, int value);
	bool Use(Resources resources, int value);

	void Update();
	void Edit();

private:
	bool isStop = false;

	float minute = 0;
	int hour = 0;
	int day = 0;
	float mulValue = 1.0f;


	int money = 0;
	int oil = 0;
	int electric = 0;
	int iron = 0;
	int citizen = 0;

	Season season = Season::Spring;
	SeasonData data;
};
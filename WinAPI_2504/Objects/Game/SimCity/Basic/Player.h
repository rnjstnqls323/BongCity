#pragma once

enum class Resources
{
	Money, Oil, Electric, Iron, Citizen, Environment, Congestion
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

	bool IsConsumeResources(InstallationData& data);

	void Update();
	void Edit();

	Season& GetSeason() { return season; }
	float& GetSpeedValue() { return speedValue; }

	void SetSpeedValue(float value) 
	{ 
		speedValue = value;  
		inversevalue = 1 / speedValue;
	}

	int& GetDay() { return day; }
	int& GetHour() { return hour; }
	int GetMinute() { return minute * inversevalue; }

	int& GetResources(Resources resources);
private:
	void AddMoney();
	void UpdateTime();
	void SetMulValue();

private:
	bool isStop = false;

	float speedValue = 1;
	float inversevalue = 1;


	float minute = 0;
	int hour = 0;
	int day = 0;
	float mulValue = 1.0f;


	int money = 10000;
	int oil = 100;
	int electric = 100;
	int iron = 100;
	int citizen = 0;
	int environment = 0;
	int congestion = 0;

	Season season = Season::Spring;
	SeasonData data;
};
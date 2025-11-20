#include "Framework.h"

Player::Player()
{
	data = DataManager::Get()->GetSeasonData((int)season); //이부분도 세이브데이터 있으면 변경하기
}

Player::~Player()
{
}

void Player::Add(Resources resources, int value)
{
	switch (resources)
	{
	case Resources::Money:
		money += value;
		break;
	case Resources::Oil:
		oil += value;
		break;
	case Resources::Electric:
		electric += value;
		break;
	case Resources::Iron:
		iron += value;
		break;
	case Resources::Citizen:
		citizen += value;
		break;
	}
}

bool Player::Use(Resources resources, int value)
{
	switch (resources)
	{
	case Resources::Money:
		if (money < value) return false;
		money -= value;
		break;
	case Resources::Oil:
		if (oil < value) return false;
		oil -= value;
		break;
	case Resources::Electric:
		if (electric < value) return false;
		electric -= value;
		break;
	case Resources::Iron:
		if (iron < value) return false;
		iron -= value;
		break;
	case Resources::Citizen:
		citizen -= value;
		break;
	}
	return true;
}

void Player::Update()
{
	if (isStop) return;

	minute += DELTA;

	if (minute > REAL_TIME*speedValue)
	{
		minute -= REAL_TIME * speedValue;
		EventManager::Get()->ExcuteEvent("SetLinearValue", nullptr);
		hour++;
		if (data.morningTime == hour)
			EventManager::Get()->ExcuteEvent("OnSun", nullptr);
		else if (data.nightTime == hour)
			EventManager::Get()->ExcuteEvent("OnMoon", nullptr);
		else if (hour == 9)
			EventManager::Get()->ExcuteEvent("OriginEmbient", nullptr);
		else if (hour == 17)
			EventManager::Get()->ExcuteEvent("SunSetEmbient", nullptr);
	}
	if (hour > DAY_HOUR)
	{
		hour -= DAY_HOUR;
		day++;
	}
	if (day > MAX_SEASON_DAY)
	{
		day -= MAX_SEASON_DAY;
		if (season == Season::Winter)
			season = Season::Spring;
		else
			season = (Season)((int)season + 1);

		data = DataManager::Get()->GetSeasonData((int)season);
	}

	int key = day % 5 + 1000;

	if (hour >= data.nightTime)
	{
		mulValue = DataManager::Get()->GetDayData(key).nightMagnification;
	}
	else if (hour >= data.afternoonTime)
	{
		mulValue = DataManager::Get()->GetDayData(key).afternoonMagnification;
	}
	else
	{
		mulValue = DataManager::Get()->GetDayData(key).morningMagnification;
	}

}

void Player::Edit()
{
	ImGui::Text("Time: %d, %f", hour, minute);
	ImGui::Text("Season: %s", season);
}

#include "Framework.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Add(Resources resources, int value)
{
}

bool Player::Use(Resources resources, int value)
{
	return false;
}

void Player::Update()
{
	if (isStop) return;

	minute += DELTA;

	if (minute > REAL_TIME)
	{
		minute -= REAL_TIME;
		hour++;
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

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
		oil += value * mulValue;
		break;
	case Resources::Electric:
		electric += value * mulValue;
		break;
	case Resources::Iron:
		iron += value * mulValue;
		break;
	case Resources::Citizen:
		citizen += value;
		break;
	case Resources::Environment:
		environment += value;
		break;
	case Resources::Congestion:
		congestion += value;
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
	case Resources::Environment:
		environment -= value;
		break;
	case Resources::Congestion:
		congestion -= value;
		break;
	}
	return true;
}

bool Player::IsConsumeResources(InstallationData& data)
{
	if (money < data.price->money) return false;
	if (oil < data.price->oil) return false;
	if (electric < data.price->electric) return false;
	if (iron < data.price->iron) return false;

	return true;
}

void Player::Update()
{
	if (isStop) return;

	UpdateTime();
	SetMulValue();
}

void Player::Edit()
{
	ImGui::Text("Time: %d, %f", hour, minute);
	ImGui::Text("Season: %s", season);
}

int& Player::GetResources(Resources resources)
{
	switch (resources)
	{
	case Resources::Money:
		return money;
	case Resources::Oil:
		return oil;
	case Resources::Electric:
		return electric;
	case Resources::Iron:
		return iron;
	case Resources::Citizen:
		return citizen;
	case Resources::Environment:
		return environment;
	case Resources::Congestion:
		return congestion;
	}
}

void Player::AddMoney()
{
	money += citizen *  environment - congestion;
}

void Player::UpdateTime()
{
	minute += DELTA;

	if (minute > REAL_TIME * speedValue)
	{
		minute -= REAL_TIME * speedValue;
		EventManager::Get()->ExcuteEvent("SetLinearValue", nullptr);
		hour++;
		InstallationManager::Get()->AddResources();
		if (data.morningTime == hour)
		{
			EventManager::Get()->ExcuteEvent("OnSun", nullptr);
			EventManager::Get()->ExcuteEvent("SKySunsetColor", nullptr);
		}
		else if (data.nightTime == hour)
		{
			EventManager::Get()->ExcuteEvent("OnMoon", nullptr);
			EventManager::Get()->ExcuteEvent("SKyNightColor", nullptr);
		}
		else if (hour == 9)
		{
			EventManager::Get()->ExcuteEvent("OriginEmbient", nullptr);
			EventManager::Get()->ExcuteEvent("SKyOriginColor", nullptr);
		}
		else if (hour == 17)
		{
			EventManager::Get()->ExcuteEvent("SunSetEmbient", nullptr);
			EventManager::Get()->ExcuteEvent("SKySunSetColor", nullptr);
		}

	}
	if (hour > DAY_HOUR)
	{
		hour -= DAY_HOUR;
		AddMoney();
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
}

void Player::SetMulValue()
{

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

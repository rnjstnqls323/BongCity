#include "Framework.h"

Production::Production()
{
}

Production::~Production()
{
}

void Production::AddResources()
{
	if (data.name.find("weapon") != string::npos)
	{
		Player::Get()->Add(Resources::Iron, data.value);
	}
	else
	{
		Player::Get()->Add(Resources::Oil, data.value);
		Player::Get()->Add(Resources::Electric, data.value);
	}
}

void Production::SetType()
{
	type = InstallationType::Production;
}

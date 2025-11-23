#include "Framework.h"

Building::Building()
{
	SetType();
}

Building::~Building()
{
}

void Building::Spawn(const Vector3 pos, int& rotation)
{
	Installation::Spawn(pos, rotation);
	Player::Get()->Add(Resources::Citizen, data.value);
}

void Building::Dispawn()
{
	Installation::Dispawn();
	Player::Get()->Use(Resources::Citizen, data.value);
}

void Building::SetType()
{
	type = InstallationType::Building;
}

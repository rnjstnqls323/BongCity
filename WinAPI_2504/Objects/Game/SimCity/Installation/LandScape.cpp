#include "Framework.h"

LandScape::LandScape()
{
	SetType();
}

LandScape::~LandScape()
{
}

void LandScape::SetType()
{
	type = InstallationType::LandScape;
}

#include "Framework.h"

Road::Road()
{
	SetType();
}

Road::~Road()
{
}

void Road::SetType()
{
	type = InstallationType::Road;
}

#include "Framework.h"


Installation::Installation()
{
	sideTiles.reserve(50);
}

Installation::~Installation()
{
}

void Installation::SetData(const int& key)
{
	data = DataManager::Get()->GetInstallationData(key);
}

void Installation::Update()
{

}

void Installation::Spawn(const Vector3 pos, int& rotation)
{
	//환경도, 혼잡도 올려주기
	//값 추가하는거 상속받아서 해주기



	transform->SetLocalPosition(pos);
	transform->SetActive(true);
	transform->SetLocalRotation(0, XMConvertToRadians(rotation), 0);
	transform->UpdateWorld();

	floorTransform->SetLocalPosition(pos.x,-0.01,pos.z);
	floorTransform->SetActive(true);
	floorTransform->SetLocalRotation(0, XMConvertToRadians(rotation), 0);
	floorTransform->SetLocalScale(data.height, 1, data.width);

	isBuild = true;

	if (data.type == InstallationType::Building)
	{
		Player::Get()->Add(Resources::Citizen, data.value);
	}
}

void Installation::Dispawn()
{
	floorTransform->SetActive(false);
	transform->SetActive(false);

	isBuild = false;

	if (data.type == InstallationType::Building)
	{
		Player::Get()->Use(Resources::Citizen, data.value);
	}
}

bool Installation::CheckResources()
{
	return false;
}

void Installation::AddResources()
{
}

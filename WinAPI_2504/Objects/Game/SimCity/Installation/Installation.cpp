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

	Player::Get()->Add(Resources::Environment, data.environment);
	Player::Get()->Add(Resources::Congestion, data.congestion);
}

void Installation::Dispawn()
{
	floorTransform->SetActive(false);
	transform->SetActive(false);

	isBuild = false;

	Player::Get()->Add(Resources::Money, data.price->money * 0.5f);
	Player::Get()->Add(Resources::Oil, data.price->oil * 0.5f);
	Player::Get()->Add(Resources::Iron, data.price->iron * 0.5f);
	Player::Get()->Add(Resources::Electric, data.price->electric * 0.5f);


	Player::Get()->Use(Resources::Environment, data.environment);
	Player::Get()->Use(Resources::Congestion, data.congestion);
}

bool Installation::CheckResources()
{
	return false;
}

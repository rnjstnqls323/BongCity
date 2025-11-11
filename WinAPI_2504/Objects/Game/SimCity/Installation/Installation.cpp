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

void Installation::Render()
{
}

void Installation::Update()
{
	if (!isSelect) return;

	//선택시 위치 옮기는거 조정하기
}

void Installation::Spawn(const Vector3 pos, int& rotation)
{
	//환경도, 혼잡도 올려주기
	//값 추가하는거 상속받아서 해주기
	transform->SetLocalPosition(pos);
	transform->SetActive(true);
	transform->SetLocalRotation(0, XMConvertToRadians(rotation), 0);
	transform->UpdateWorld();
	isBuild = true;
}

void Installation::Dispawn()
{
	transform->SetActive(false);
	isBuild = false;
}

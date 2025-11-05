#include "Framework.h"


Installation::Installation()
{
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

void Installation::Build(const Vector3 pos)
{
	//환경도, 혼잡도 올려주기
	//값 추가하는거 상속받아서 해주기
	this->localPosition = pos;
	isBuild = true;
}

void Installation::Distroy()
{
}

void Installation::Init()
{
	CreateModel();
}

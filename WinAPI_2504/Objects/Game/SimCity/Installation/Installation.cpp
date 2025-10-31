#include "Framework.h"


Installation::Installation()
{
}

Installation::~Installation()
{
	delete model;
}

void Installation::SetData(const int& key)
{
	data = DataManager::Get()->GetInstallationData(key);
}

void Installation::Render()
{
	model->Render();
}

void Installation::Update()
{
	if (!isSelect) return;

	//선택시 위치 옮기는거 조정하기
}

void Installation::Init()
{
	CreateModel();
}

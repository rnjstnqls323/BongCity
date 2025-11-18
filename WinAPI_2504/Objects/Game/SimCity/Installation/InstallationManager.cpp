#include "Framework.h"

InstallationManager::InstallationManager()
{
	CreateInstallation();
}

InstallationManager::~InstallationManager()
{
	for (auto& installation : installations)
	{
		delete installation.second.first;

		for (Installation* install : installation.second.second)
		{
			delete install;
		}
	}
	for (int key : DataManager::Get()->GetKeys())
	{
		delete showInstallations[key];
	}
}

void InstallationManager::Update()
{
}

void InstallationManager::Render()
{
	for (auto& installation : installations)
	{
		installation.second.first->Render();
	}
	for (int key : DataManager::Get()->GetKeys())
	{
		if (UIManager::Get()->GetMode() != Mode::Build)return;
		if (!showInstallations[key]->IsActive()) continue;
		showInstallations[key]->Render();
	}
}

void InstallationManager::Edit()
{
}

void InstallationManager::SpawnInstallation(InstallationData& data, Vector3 pos, Index2& index, int& rotation)
{
	vector<Installation*>& installation = installations[data.key].second;

	for (Installation* install : installation)
	{
		if(install->GetTransform()->IsActive())continue;
		install->SetCenterIndex(index);

		Vector3 addPos;

		addPos.x = data.height * 0.5f;
		addPos.z = -data.width * 0.5f;

		install->Spawn(pos + addPos, rotation);
		break;
	}

	installations[data.key].first->UpdateTransform();
}

void InstallationManager::DispawnInstallation(int& key, Index2& index)
{
	Installation* installation = GetTransformToIndex(key, index);
	installation->Dispawn();
	installations[key].first->UpdateTransform();
}

void InstallationManager::ShowInstallationToMouse(InstallationData& data, Vector3 pos, Index2& index, int& rotation)
{
	
	if (data.key == InstallationData().key)
	{
		if (preSelectKey != data.key)
		{
			showInstallations[preSelectKey]->SetActive(false);
			preSelectKey = data.key;
		}
		return;
	}

	if (preSelectKey != data.key)
	{
		if(preSelectKey != 0)
			showInstallations[preSelectKey]->SetActive(false);
		preSelectKey = data.key;

		showInstallations[data.key]->SetActive(true);
	}

	Vector3 addPos;
	addPos.x = data.height * 0.5f;
	addPos.z = -data.width * 0.5f;

	showInstallations[data.key]->SetLocalPosition(pos + addPos);
	showInstallations[data.key]->SetLocalRotation(0, XMConvertToRadians(rotation), 0);
	showInstallations[data.key]->UpdateWorld();

}



void InstallationManager::CreateInstallation()
{

	for (int key : DataManager::Get()->GetKeys())
	{
		string name = DataManager::Get()->GetInstallationData(key).name;
		installations[key] =
		{
			new InstallationInstancing(name, MAX_SIZE),
			vector<Installation*>()
		};
		showInstallations[key] = new Model(name);
		showInstallations[key]->SetActive(false);
		showInstallations[key]->SetLocalScale(0.03, 0.03, 0.03);
	}
	for (int key : DataManager::Get()->GetKeys())
	{
		installations[key].second.reserve(MAX_SIZE);
		for (int i = 0; i < MAX_SIZE; i++)
		{
			Installation* installation = new Installation;
			installation->SetData(key);
			installation->SetTransform(installations[key].first->Add());

			installation->GetTransform()->SetActive(false);
			installation->GetTransform()->SetLocalScale(0.03,0.03,0.03);
			installations[key].second.push_back(installation);
		}
	}
}

Installation*& InstallationManager::GetTransformToIndex(int& key, Index2& index)
{
	vector<Installation*>& installation = installations[key].second;
	for (Installation* install : installation)
	{
		if (!install->GetTransform()->IsActive()) continue;
		if (install->GetCenterIndex() != index)continue;

		return install;
	}
}

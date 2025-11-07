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

		for (int i = 0; i < installation.second.second.size(); i++)
		{
			delete installation.second.second[i];
		}
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
}

void InstallationManager::Edit()
{
}

bool InstallationManager::SpawnInstallation(int& key, Vector3 pos, Index2& index)
{
	vector<Installation*>& installation = installations[key].second;
	for (int i = 0; i < installation.size(); i++)
	{
		if (installation[i]->GetTransform()->IsActive())continue;

		installation[i]->SetCenterIndex(index);
		if (!installation[i]->CheckSide()) return false;

		Transform* transform = installation[i]->GetTransform();
		transform->SetActive(true);

		Vector3 addPos;

		addPos.x = installation[i]->GetData().height * 0.5f;
		addPos.z = -installation[i]->GetData().width * 0.5f;

		transform->SetLocalPosition(pos + addPos);
		break;
	}
	installations[key].first->UpdateTransform();

	return true;
}



void InstallationManager::CreateInstallation()
{

	for (int key : DataManager::Get()->GetKeys())
	{
		installations[key] =
		{
			new InstallationInstancing(DataManager::Get()->GetInstallationData(key).name, MAX_SIZE),
			vector<Installation*>()
		};
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

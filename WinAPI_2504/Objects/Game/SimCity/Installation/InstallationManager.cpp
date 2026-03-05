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
	delete floors;
}

void InstallationManager::Update()
{
	for (Installation* install : spawnInstallations)
	{
		install->Update();
	}
}

void InstallationManager::Render()
{
	floors->Render();

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

bool InstallationManager::SpawnInstallation(InstallationData& data, Vector3 pos, Index2& index, int& rotation)
{
	vector<Installation*>& installation = installations[data.key].second;

	if (!UseMoney(data)) return false;

	for (Installation* install : installation)
	{
		if(install->GetTransform()->IsActive())continue;
		install->SetCenterIndex(index);

		Vector3 addPos;

		addPos.x = data.height * 0.5f;
		addPos.z = -data.width * 0.5f;

		install->Spawn(pos + addPos, rotation);

		spawnInstallations.insert(install);

		floors->UpdateTransform();

		break;
	}

	installations[data.key].first->UpdateTransform();
	return true;
}

void InstallationManager::DispawnInstallation(int& key, Index2& index)
{
	Installation* installation = GetTransformToIndex(key, index);
	installation->Dispawn();
	auto it = spawnInstallations.find(installation);
	if (it != spawnInstallations.end())
	{
		spawnInstallations.erase(it);
	}
	installations[key].first->UpdateTransform();
	floors->UpdateTransform();
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

void InstallationManager::AddResources()
{
	for (Installation* install : spawnInstallations)
	{
		if (install->GetType() != InstallationType::Production) continue;
		Production* production = (Production*)install;

		production->AddResources();
	}
}




bool InstallationManager::UseMoney(InstallationData& data)
{
	if (!Player::Get()->IsConsumeResources(data)) return false;

	Player::Get()->Use(Resources::Money, data.price->money);
	Player::Get()->Use(Resources::Oil, data.price->oil);
	Player::Get()->Use(Resources::Iron, data.price->iron);
	Player::Get()->Use(Resources::Electric, data.price->electric);

	return true;
}

void InstallationManager::CreateInstallation()
{
	int size = DataManager::Get()->GetKeys().size();
	floors = new FloorInstancing(L"Resources/Textures/SimCity/UI/BackGround/floor.jpg", MAX_SIZE * size);
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
			Installation* installation = nullptr;
			switch (DataManager::Get()->GetInstallationData(key).type)
			{
			case InstallationType::Road:
				installation = new Road();
				break;
			case InstallationType::Building:
				installation = new Building();
				break;
			case InstallationType::Production:
				installation = new Production();
				break;
			case InstallationType::LandScape:
				installation = new LandScape();
				break;
			}
			installation->SetData(key);
			installation->SetTransform(installations[key].first->Add());

			installation->GetTransform()->SetActive(false);
			installation->GetTransform()->SetLocalScale(0.03,0.03,0.03);
			installation->SetFloorTransform(floors->Add());

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

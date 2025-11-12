#include "Framework.h"
#include "ModelRenderScene.h"

ModelRenderScene::ModelRenderScene()
{
	keys = DataManager::Get()->GetKeys();
	for (int key : keys)
	{
		string name = DataManager::Get()->GetInstallationData(key).name;
		showInstallations[key] = new Model(name);
		showInstallations[key]->SetLocalScale(0.03, 0.03, 0.03);
	}
}

ModelRenderScene::~ModelRenderScene()
{
	for (int key : keys)
	{
		delete showInstallations[key];
	}
}

void ModelRenderScene::Update()
{
	if (Input::Get()->IsKeyDown('Q')&& count<keys.size())
	{
		count++;
		showInstallations[keys[count]]->SetLocalPosition(showInstallations[keys[count - 1]]->GetLocalPosition());
	}
	if (Input::Get()->IsKeyDown('E')&&count>0)
	{
		count--;
		showInstallations[keys[count]]->SetLocalPosition(showInstallations[keys[count + 1]]->GetLocalPosition());
	}
	showInstallations[keys[count]]->UpdateWorld();
	//model2->UpdateWorld();
}

void ModelRenderScene::PreRender()
{
}

void ModelRenderScene::Render()
{
	showInstallations[keys[count]]->Render();
	//model2->Render();
}

void ModelRenderScene::PostRender()
{
}

void ModelRenderScene::GUIRender()
{
	showInstallations[keys[count]]->Edit();
	//model2->Edit();
}

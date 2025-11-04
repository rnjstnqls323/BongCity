#include "Framework.h"
#include "ModelRenderScene.h"

ModelRenderScene::ModelRenderScene()
{
	model = new Model("building_landscape_school");
	//model->SetTag("road1");
	//model2 = new Model("Road_L");
	//model2->SetTag("road2");
}

ModelRenderScene::~ModelRenderScene()
{
	delete model;
	//delete model2;
}

void ModelRenderScene::Update()
{
	model->UpdateWorld();
	//model2->UpdateWorld();
}

void ModelRenderScene::PreRender()
{
}

void ModelRenderScene::Render()
{
	model->Render();
	//model2->Render();
}

void ModelRenderScene::PostRender()
{
}

void ModelRenderScene::GUIRender()
{
	model->Edit();
	//model2->Edit();
}

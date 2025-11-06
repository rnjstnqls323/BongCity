#include "Framework.h"
#include "ModelInstancingScene.h"

ModelInstancingScene::ModelInstancingScene()
{
	//  modelInstancing = new ModelAnimatorInstancing("Naruto");
	//  
	//  modelInstancing->ReadClip("Idle");
	//  modelInstancing->ReadClip("Run");
	//  modelInstancing->ReadClip("Attack");
	//  
	//  modelInstancing->CreateTexture();
	//  
	//  
	transforms.reserve(200);
	  for (float z = -40.0f; z <= 50.0f; z++)
	  {
	  	for (float x = -40.0f; x <= 50.0f; x++)
	  	{
	  		//Model* model = new Model("Naruto");
	  		//model->SetLocalPosition(x, 0.0f, z);
	  		////model->SetLocalScale(0.01f, 0.01f, 0.01f);
	  		//model->UpdateWorld();
	  		//models.push_back(model);
	  
			Transform* transform = new Transform();
	  		transform->SetLocalPosition(x, 0.0f, z);
	  		//transform->SetLocalScale(0.01f, 0.01f, 0.01f);

			transforms.push_back(transform);
	  	}
	  }
	//  
	//  //modelInstancing->Update();

	instan = new QuadInstancing(L"Resources/Textures/Test.jfif", 10000);
}

ModelInstancingScene::~ModelInstancingScene()
{
	//for (Model* model : models)
	//	delete model;
	//delete modelInstancing;
	delete instan;

}

void ModelInstancingScene::Update()
{
	//modelInstancing->Update();
	instan->Update(transforms);
}

void ModelInstancingScene::PreRender()
{
}

void ModelInstancingScene::Render()
{
	//for (Model* model : models)
	//{
	//	if (CAM->ContainPoint(model->GetGlobalPosition()))
	//		model->Render();
	//}

	instan->Render();
}

void ModelInstancingScene::PostRender()
{
}

void ModelInstancingScene::GUIRender()
{
	// ImGui::DragInt("Index", &instanceIndex);
	// ImGui::DragInt("Clip", &clip);
	// 
	// if (ImGui::Button("Play"))
	// 	modelInstancing->PlayClip(instanceIndex, clip);
	// 
	// modelInstancing->Edit();
}

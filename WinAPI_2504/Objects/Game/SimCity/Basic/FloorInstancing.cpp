#include "Framework.h"

FloorInstancing::FloorInstancing(wstring path, int size):Plane(Vector2{1,1})
{
	this->size = size;
	material->SetDiffuseMap(L"Resources/Textures/SimCity/UI/BackGround/floor.jpg");
	material->SetShader(L"Instancing/ModelInstancing.hlsl");

	instanceDatas = new InstanceData[size];
	instanceBuffer = new VertexBuffer(instanceDatas, sizeof(InstanceData), size);

	transforms.reserve(size);
}

FloorInstancing::~FloorInstancing()
{
	delete[] instanceDatas;
	delete instanceBuffer;

	for (Transform* transform : transforms)
	{
		delete transform;
	}
}

void FloorInstancing::UpdateTransform()
{
	drawCount = 0;
	for (Transform* t : transforms)
	{
		if (!t->IsActive())continue;
		t->UpdateWorld();
		instanceDatas[drawCount].world = XMMatrixTranspose(t->GetWorld());
		drawCount++;
	}
	instanceBuffer->Update(instanceDatas, drawCount);


}

void FloorInstancing::Render()
{
	instanceBuffer->Set(1);
	GetMaterial()->Set();
	mesh->DrawInstanced(drawCount);
	//타일은 안줄어들어서 size로 맞춰도되는데, floorInstancing은 갯수 늘었다 줄었다해서 count로 맞춰줘야됨.
}

void FloorInstancing::Edit()
{
	int count = 0;
	for (Transform* transform : transforms)
	{
		transform->SetTag(to_string(count++));
		transform->Edit();
	}
}

void FloorInstancing::UpdateInstanceBuffer()
{
	instanceBuffer->Update(instanceDatas, drawCount);
}

Transform* FloorInstancing::Add()
{
	Transform* transform = new Transform;
	transforms.push_back(transform);
	transform->SetActive(false);
	return transform;
}


#include "Framework.h"

QuadInstancing::QuadInstancing(wstring path, int size):Quad(path, true)
{
	this->size = size;
	material->SetShader(L"Instancing/QuadInstancing.hlsl");

	instanceDatas = new InstanceData[size];
	instanceBuffer = new VertexBuffer(instanceDatas, sizeof(InstanceData), size);
}
QuadInstancing::~QuadInstancing()
{
	delete[] instanceDatas;
	delete instanceBuffer;
}

void QuadInstancing::UpdateSelectTile()
{
	Ray ray = CAM->ScreenPointToRay(mousePos);
	float t = -ray.origin.y / ray.direction.y;


	Vector3 hitPos = ray.origin + ray.direction * t;
	Index2 ind = { (int)-(hitPos.z - 100), (int)hitPos.x };

	int testIndex = ind.ChangeToInt(100);

	for (int i = 0; i < size; i++)
	{
		if (i == testIndex)
			instanceDatas[i].color = Float4(1, 0, 0, 1);
		else
			instanceDatas[i].color = Float4(1, 1, 1, 1);
	}

	instanceBuffer->Update(instanceDatas, size);
}

void QuadInstancing::UpdateTransform()
{
	drawCount = 0;
	for (Transform* t : transforms)
	{		
		t->UpdateWorld();
		instanceDatas[drawCount].world = XMMatrixTranspose(t->GetWorld());
		drawCount++;
	}
	instanceBuffer->Update(instanceDatas, drawCount);
}

void QuadInstancing::Render()
{
    instanceBuffer->Set(1);
    GetMaterial()->Set();
    mesh->DrawInstanced(size);

}
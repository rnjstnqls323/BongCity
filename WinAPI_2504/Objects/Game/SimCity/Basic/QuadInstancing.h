#pragma once

class QuadInstancing : public Quad
{
public:
	QuadInstancing(wstring path, int size);
	~QuadInstancing();

	void Render();

	template<typename T>
	void Update(T& transform)
	{
		drawCount = 0;
		for (Transform* t : transform)
		{
			if (!t->IsActive()) continue;
			if (!CAM->ContainPoint(t->GetGlobalPosition())) continue;

			t->UpdateWorld();
			instanceDatas[drawCount] = XMMatrixTranspose(t->GetWorld());
			drawCount++;
		}
		instanceBuffer->Update(instanceDatas, drawCount);
	}
private:
	int size;
	int drawCount;

	VertexBuffer* instanceBuffer;
	Matrix* instanceDatas;
};
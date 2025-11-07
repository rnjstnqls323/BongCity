#pragma once

class QuadInstancing : public Quad
{
private:
	struct InstanceData
	{
		Matrix world;
		Float4 color;

		InstanceData()
		{
			world = XMMatrixIdentity();
			color = Float4(1, 1, 1, 1);
		}
	};

public:
	QuadInstancing(wstring path, int size);
	~QuadInstancing();

	void UpdateSelectTile();

	void UpdateTransform();
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
			instanceDatas[drawCount].world = XMMatrixTranspose(t->GetWorld());
			drawCount++;
		}
		instanceBuffer->Update(instanceDatas, drawCount);
	}

	Transform* Add()
	{
		Transform* transform = new Transform();
		transforms.push_back(transform);
		return transform;
	}

private:
	int size;
	int drawCount;

	VertexBuffer* instanceBuffer;
	InstanceData* instanceDatas;

	vector<Transform*> transforms;
};
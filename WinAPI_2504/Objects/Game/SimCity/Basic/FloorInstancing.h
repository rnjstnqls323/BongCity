#pragma once

class FloorInstancing :public Plane
{
public:
	FloorInstancing(wstring path, int size);
	~FloorInstancing();

	void UpdateTransform();
	void Render();

	void Edit() override;

	void UpdateInstanceBuffer();

	Transform* Add();
private:

private:
	int size;
	int drawCount;

	VertexBuffer* instanceBuffer;
	InstanceData* instanceDatas;

	vector<Transform*> transforms;
};
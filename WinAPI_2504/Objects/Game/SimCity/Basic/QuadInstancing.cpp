#include "Framework.h"

QuadInstancing::QuadInstancing(wstring path, int size):Quad(path, true)
{
	this->size = size;
	material->SetShader(L"Instancing/QuadInstancing.hlsl");

	instanceDatas = new Matrix[size];
	instanceBuffer = new VertexBuffer(instanceDatas, sizeof(Matrix), size);
}
QuadInstancing::~QuadInstancing()
{
	delete[] instanceDatas;
	delete instanceBuffer;
}

void QuadInstancing::Render()
{
    instanceBuffer->Set(1);
    GetMaterial()->Set();
    mesh->DrawInstanced(size);

}
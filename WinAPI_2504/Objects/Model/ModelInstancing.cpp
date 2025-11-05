#include "Framework.h"

ModelInstancing::ModelInstancing(string name, UINT size)
	: Model(name), size(size)
{
    SetShader(L"Instancing/ModelInstancing.hlsl");
    instanceDatas = new Matrix[size];
    instanceBuffer = new VertexBuffer(instanceDatas, sizeof(Matrix), size);
}

ModelInstancing::~ModelInstancing()
{
    delete[] instanceDatas;
    delete instanceBuffer;
}


void ModelInstancing::Update(vector<Transform*>& transforms)
{
    drawCount = 0;
    for (int i = 0; i < transforms.size(); i++)
    {
        if (!transforms[i]->IsActive()) continue;

        transforms[i]->UpdateWorld();
        instanceDatas[drawCount] = XMMatrixTranspose(transforms[i]->GetWorld());

        drawCount++;
    }
    instanceBuffer->Update(instanceDatas, drawCount);
}

void ModelInstancing::Render()
{
    instanceBuffer->Set(1);

    for (ModelMesh* mesh : meshes)
        mesh->RenderInstanced(drawCount);
}

void ModelInstancing::Edit()
{
    ImGui::Text("DrawCount : %d", drawCount);

    Model::Edit();
}
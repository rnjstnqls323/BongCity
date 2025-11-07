#include "Framework.h"

InstallationInstancing::InstallationInstancing(string name, UINT size) : Model(name), size(size)
{
    SetShader(L"Instancing/ModelInstancing.hlsl");
    instanceDatas = new Matrix[size];
    instanceBuffer = new VertexBuffer(instanceDatas, sizeof(Matrix), size);

    transforms.reserve(size);
}

InstallationInstancing::~InstallationInstancing()
{
    delete[] instanceDatas;
    delete instanceBuffer;

    for (Transform* transform : transforms)
    {
        delete transform;
    }
}

void InstallationInstancing::UpdateTransform()
{
    //이거 설치했을때 기준으로 업데이트해줄까?

    drawCount = 0;
    for (Transform* transform : transforms)
    {
        if (!transform->IsActive()) continue;

        transform->UpdateWorld();
        instanceDatas[drawCount] = XMMatrixTranspose(transform->GetWorld());

        drawCount++;
    }
    instanceBuffer->Update(instanceDatas, drawCount);
}

void InstallationInstancing::UpdateSelect()
{
    //이거 실시간으로 위치바뀌게하고싶은데 
    //프레임 떨어질 것 같아서 일단 보류
}


void InstallationInstancing::Render()
{
    instanceBuffer->Set(1);

    for (ModelMesh* mesh : meshes)
        mesh->RenderInstanced(drawCount);
}

void InstallationInstancing::Edit()
{
}

Transform* InstallationInstancing::Add()
{
    Transform* transform = new Transform;
    transforms.insert(transform);
    return transform;
}

bool InstallationInstancing::Delete(Transform* transform)
{
    return false;
}

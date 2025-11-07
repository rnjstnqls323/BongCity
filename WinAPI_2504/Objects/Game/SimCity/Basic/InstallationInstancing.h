#pragma once

class InstallationInstancing : public Model
{
public:
    InstallationInstancing(string name, UINT size);
    ~InstallationInstancing();

    void UpdateTransform();
    void UpdateSelect();
    void Render();
    void Edit();

    Transform* Add();
    bool Delete(Transform* transform);


private:
    unordered_set<Transform*> transforms;
    Matrix* instanceDatas;
    VertexBuffer* instanceBuffer;

    UINT drawCount;
    UINT size;
};
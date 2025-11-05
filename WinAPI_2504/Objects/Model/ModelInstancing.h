#pragma once

class ModelInstancing : public Model
{
public:
    ModelInstancing(string name, UINT size);
    ~ModelInstancing();

    void Update(vector<Transform*>& transforms);
    void Render();
    void Edit();

private:
    Matrix* instanceDatas;

    VertexBuffer* instanceBuffer;

    UINT drawCount;
    UINT size;
};
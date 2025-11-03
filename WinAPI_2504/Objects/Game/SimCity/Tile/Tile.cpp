#include "Framework.h"

Tile::Tile() : GameObject(L"Basic/Collider.hlsl")
{
	MakeMesh();
	SetColor(0, 1, 0);
}

Tile::~Tile()
{
	delete mesh;
}

void Tile::Render()
{
    if (!isActive) return;

    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    material->Set();

    //mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}
void Tile::MakeMesh()
{
	mesh = new Mesh<Vertex>();

	Vector2 halfSize = size * 0.5f;

	vector<Vertex>& vertices = mesh->GetVertices();

	vertices.emplace_back(-halfSize.x, +halfSize.y, 0.0f);
	vertices.emplace_back(+halfSize.x, +halfSize.y, 0.0f);
	vertices.emplace_back(-halfSize.x, -halfSize.y, 0.0f);
	vertices.emplace_back(+halfSize.x, -halfSize.y, 0.0f);

	vector<UINT>& indices = mesh->GetIndices();

	indices = { 0, 1, 2, 2, 1, 3 };
}

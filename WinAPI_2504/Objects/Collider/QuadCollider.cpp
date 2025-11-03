#include "Framework.h"

QuadCollider::QuadCollider(Vector2 size):size(size)
{
	type = Type::Quad;

	MakeMesh();
	mesh->CreateMesh();

}

QuadCollider::~QuadCollider()
{
	delete mesh;
}

bool QuadCollider::IsRayCollision(const Ray& ray, RayHit* hitInfo)
{
	//이거는 처리해주면됨
    return false;
}
void QuadCollider::MakeMesh()
{
	mesh = new Mesh<Vertex>();

	Vector2 halfSize = size * 0.5f;

	vector<Vertex>& vertices = mesh->GetVertices();

	vertices.emplace_back(-halfSize.x, +halfSize.y, 0.0f);
	vertices.emplace_back(+halfSize.x, +halfSize.y, 0.0f);
	vertices.emplace_back(-halfSize.x, -halfSize.y, 0.0f);
	vertices.emplace_back(+halfSize.x, -halfSize.y, 0.0f);

	vector<UINT>& indices = mesh->GetIndices();

	indices = { 0,1,1,3,3,2,2,0};
}

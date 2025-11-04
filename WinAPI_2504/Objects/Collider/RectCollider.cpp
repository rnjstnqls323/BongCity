#include "Framework.h"

RectCollider::RectCollider(Vector2 size):size(size)
{
	type = Type::Quad;

	MakeMesh();
	mesh->CreateMesh();

}

RectCollider::~RectCollider()
{
	delete mesh;
}

bool RectCollider::IsRayCollision(const Ray& ray, RayHit* hitInfo)
{
    if (!IsActive()) return false;

    Vector3 center = localPosition;
    Vector2 half = size * 0.5f;

    float planeY = center.y;

    if (fabs(ray.direction.y) < FLT_EPSILON)
        return false;

    float t = (planeY - ray.origin.y) / ray.direction.y;
    if (t < 0.0f)
        return false; // 뒤쪽 교차 무시

    // 평면 위의 교차 지점 계산
    Vector3 hitPos = ray.origin + ray.direction * t;

    if (hitPos.x < center.x - half.x || hitPos.x > center.x + half.x)
        return false;
    if (hitPos.z < center.z - half.y || hitPos.z > center.z + half.y)
        return false;

    if (hitInfo)
    {
        hitInfo->isHit = true;
        hitInfo->distance = t;
        hitInfo->position = hitPos;
        hitInfo->normal = Vector3(0, 1, 0); // 평면 위이므로 위쪽 노멀
    }

    return true;
}


void RectCollider::Update()
{
	UpdateWorld();
}
void RectCollider::MakeMesh()
{
	mesh = new Mesh<Vertex>();

	Vector2 halfSize = size * 0.5f;

	vector<Vertex>& vertices = mesh->GetVertices();

	vertices.emplace_back(-halfSize.x, 0,+halfSize.y);
	vertices.emplace_back(+halfSize.x, 0,+halfSize.y);
	vertices.emplace_back(-halfSize.x, 0,-halfSize.y);
	vertices.emplace_back(+halfSize.x, 0,-halfSize.y);

	vector<UINT>& indices = mesh->GetIndices();

	indices = { 0,1,1,3,3,2,2,0};
}

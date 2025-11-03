#pragma once

class RectCollider :public Collider
{
public:
	RectCollider(Vector2 size);
	~RectCollider();

	bool IsRayCollision(const Ray& ray, RayHit* hitInfo) override;
	bool IsBoxCollision(BoxCollider* collider) override { return false; }
	bool IsSphereCollision(SphereCollider* collider) override { return false; }
	bool IsCapsuleCollision(CapsuleCollider* collider) override {return false;}

private:
	void MakeMesh() override;

private:
	Vector2 size;
};
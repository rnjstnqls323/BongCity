#pragma once

class QuadCollider :public Collider
{
public:
	QuadCollider(Vector2 size);
	~QuadCollider();

	bool IsRayCollision(const Ray& ray, RayHit* hitInfo) override;
	bool IsBoxCollision(BoxCollider* collider) override { return false; }
	bool IsSphereCollision(SphereCollider* collider) override { return false; }
	bool IsCapsuleCollision(CapsuleCollider* collider) override {return false;}

private:
	void MakeMesh() override;

private:
	Vector2 size;
};
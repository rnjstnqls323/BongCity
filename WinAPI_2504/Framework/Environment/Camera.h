#pragma once

class Camera : public Transform
{
private:
	const int MAX_ROTATION_X = 40;
	const int MAX_POSITION_Y = 50;

	const int MIN_WHEEL_POSITION_Y = 11;
	const int MAX_WHEEL_POSITION_Y = 80;

	const int TILE_SIZE = 150;


	const float SMOOTH_SPEED = 5.0f;
	const float EPSILON = 0.1f;
	const float WHEEL = -0.02f; //±âº» ÈÙ ÇÝÆ½ 120¾¿ ¿òÁ÷ÀÓ


public:
	Camera();
	~Camera();

	void Update();
	void Edit();

	void SetView(UINT slot = 1);

	void SetTarget(Transform* target);

	class Ray ScreenPointToRay(Vector3 screenPos);	
	Vector3 WorldToScreenPoint(Vector3 worldPos);

	bool ContainPoint(Vector3 point);
	bool ContainSphere(Vector3 center, float radius);

private:
	void FreeMode();
	void FollowMode();

	void FrustumUpdate();

private:
	bool isMatch;
	float nextPositionY;
	float nextRotationX;

	float moveSpeed = 30.0f;
	float rotSpeed = 10.0f;
	Vector3 prevMousePos;

	Vector3 startPos = { 90,0,-50 };

	Matrix view;
	Matrix projection;
	ViewBuffer* viewBuffer;	

	Transform* target = nullptr;	

	float distance = 20.0f;
	float height = 20.0f;
	float moveDamping = 5.0f;
	float rotDamping = 1.0f;
	float destRot = 0.0f;

	Vector3 destPos;
	Vector3 focusOffset;

	Matrix rotMatrix;

	bool isLookAtTargetX = true;
	bool isLookAtTargetY = true;

	Vector3 planes[6];
	float a, b, c, d;
};
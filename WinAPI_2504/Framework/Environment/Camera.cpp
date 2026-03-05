#include "Framework.h"

Camera::Camera()
{
	tag = "Camera";

	viewBuffer = new ViewBuffer();
    localPosition = startPos;
}

Camera::~Camera()
{
	delete viewBuffer;
}

void Camera::Update()
{
	projection = Environment::Get()->GetPerspective();

    FrustumUpdate();

    if (target)
        FollowMode();
    else
	    FreeMode();

	UpdateWorld();		

    Input::Get()->ClearMouseWheel();
}

void Camera::Edit()
{
	ImGui::DragFloat("MoveSpeed", &moveSpeed, 0.1f, 0.1f, 100.0f);
	ImGui::DragFloat("RotSpeed", &rotSpeed, 0.1f, 0.1f, 100.0f);

    if (target)
    {
        ImGui::DragFloat("Distance", &distance);
        ImGui::DragFloat("Height", &height);

        ImGui::DragFloat("MoveDamping", &moveDamping, 0.1f);
        ImGui::DragFloat("RotDamping", &rotDamping, 0.1f);

        ImGui::DragFloat3("FocusOffset", (float*)&focusOffset, 0.1f);

        ImGui::Checkbox("LookAtTargetX", &isLookAtTargetX);
        ImGui::Checkbox("LookAtTargetY", &isLookAtTargetY);

        //ImGui::InputText("File", file, 128);
        //
        //if (ImGui::Button("Save"))
        //    TargetOptionSave(file);
        //
        //ImGui::SameLine();
        //
        //if (ImGui::Button("Load"))
        //    TargetOptionLoad(file);
    }

    Transform::Edit();
}

void Camera::SetView(UINT slot)
{
    view = XMMatrixInverse(nullptr, world);
    viewBuffer->Set(view, world);
    viewBuffer->SetVS(slot);
}

void Camera::SetTarget(Transform* target)
{
    this->target = target;

    if (target != nullptr)
    {
        nextPositionY = MAX_POSITION_Y;
        nextRotationX = XMConvertToRadians(MAX_ROTATION_X);
    }
    else
    {
        nextPositionY = MAX_POSITION_Y*0.5f;
        nextRotationX = XMConvertToRadians(MAX_ROTATION_X*0.5f);
    }
    Input::Get()->ClearMouseWheel();
    isMatch = false;
}

Ray Camera::ScreenPointToRay(Vector3 screenPos)
{
    Vector3 screenSize(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f);    

    Vector2 point;
	point.x = (screenPos.x / screenSize.x) * 2.0f - 1.0f;
	point.y = (screenPos.y / screenSize.y) * 2.0f - 1.0f;
	//-> 0~screen -> -1~1

    Float4x4 temp;
    XMStoreFloat4x4(&temp, projection);

	screenPos.x = point.x / temp._11;
	screenPos.y = point.y / temp._22;
    screenPos.z = 1.0f;

    screenPos = XMVector3TransformNormal(screenPos, world);

    Ray ray;
	ray.origin = localPosition;
	ray.direction = screenPos.GetNormalized();

    return ray;
}

Vector3 Camera::WorldToScreenPoint(Vector3 worldPos)
{
    Vector3 screenPos;

    screenPos = worldPos * view;
	screenPos = screenPos * projection;

	screenPos = (screenPos + Vector3(1.0f, 1.0f, 1.0f)) * 0.5f;//-1~1 -> 0~1

	screenPos.x *= SCREEN_WIDTH;
	screenPos.y *= SCREEN_HEIGHT;

    return screenPos;
}

bool Camera::ContainPoint(Vector3 point)
{
    for (int i = 0; i < 6;i++)
    {
        Vector3 dot = XMPlaneDotCoord(planes[i], point);

        if (dot.x < 0.0f)
            return false;
    }

    return true;
}

bool Camera::ContainSphere(Vector3 center, float radius)
{
    return false;
}

void Camera::FreeMode()
{
    NormalCamera();

    if (!isMatch)return;

    float scrollDelta = Input::Get()->GetMouseWheel() * WHEEL;
    float targetZ = localPosition.z - nextPositionY + localPosition.y;

    nextPositionY += scrollDelta;
    nextPositionY = GameMath::Clamp(nextPositionY, MIN_WHEEL_POSITION_Y, 50);

    // 카메라 보간
    localPosition.y = GameMath::Lerp(localPosition.y, nextPositionY, DELTA * SMOOTH_SPEED);
    // z 이동을 y 변화량에 비례
    localPosition.z = GameMath::Lerp(localPosition.z, targetZ, DELTA * SMOOTH_SPEED);
    localRotation.x = GameMath::Lerp(localRotation.x, XMConvertToRadians(nextPositionY), DELTA * SMOOTH_SPEED);

}

void Camera::FollowMode()
{
    NormalCamera();
    if (!isMatch)return;

    
    //nextPositionY += Input::Get()->GetMouseWheel() * WHEEL;
    //if (nextPositionY != 0 && nextPositionY >= MIN_WHEEL_POSITION_Y && nextPositionY <= MAX_WHEEL_POSITION_Y)
    //{
    //    localPosition.y = GameMath::Lerp(localPosition.y, nextPositionY, DELTA * SMOOTH_SPEED);
    //    localPosition.z = GameMath::Lerp(localPosition.z, -nextPositionY, DELTA * SMOOTH_SPEED);
    //}
    float scrollDelta = Input::Get()->GetMouseWheel() * WHEEL;
    float targetZ = localPosition.z - nextPositionY +localPosition.y;

    nextPositionY += scrollDelta;
    nextPositionY = GameMath::Clamp(nextPositionY, MIN_WHEEL_POSITION_Y, MAX_WHEEL_POSITION_Y);

    // 카메라 보간
    localPosition.y = GameMath::Lerp(localPosition.y, nextPositionY, DELTA * SMOOTH_SPEED);

    // z 이동을 y 변화량에 비례
    localPosition.z = GameMath::Lerp(localPosition.z, targetZ, DELTA * SMOOTH_SPEED);
}

void Camera::FrustumUpdate()
{
    Float4x4 VP;
    XMStoreFloat4x4(&VP, view * projection);

    //Left
    a = VP._14 + VP._11;
    b = VP._24 + VP._21;
    c = VP._34 + VP._31;
    d = VP._44 + VP._41;
    planes[0] = XMVectorSet(a, b, c, d);

    //Right
    a = VP._14 - VP._11;
    b = VP._24 - VP._21;
    c = VP._34 - VP._31;
    d = VP._44 - VP._41;
    planes[1] = XMVectorSet(a, b, c, d);

    //Bottom
    a = VP._14 + VP._12;
    b = VP._24 + VP._22;
    c = VP._34 + VP._32;
    d = VP._44 + VP._42;
    planes[2] = XMVectorSet(a, b, c, d);

    //Top
    a = VP._14 - VP._12;
    b = VP._24 - VP._22;
    c = VP._34 - VP._32;
    d = VP._44 - VP._42;
    planes[3] = XMVectorSet(a, b, c, d);

    //Near
    a = VP._14 + VP._13;
    b = VP._24 + VP._23;
    c = VP._34 + VP._33;
    d = VP._44 + VP._43;
    planes[4] = XMVectorSet(a, b, c, d);

    //Far
    a = VP._14 - VP._13;
    b = VP._24 - VP._23;
    c = VP._34 - VP._33;
    d = VP._44 - VP._43;
    planes[5] = XMVectorSet(a, b, c, d);

    for(int i=0;i<6;i++)
        planes[i] = XMPlaneNormalize(planes[i]);
}

void Camera::NormalCamera()
{
    if (Input::Get()->IsKeyPress('W'))
        SetLocalPosition(localPosition.x, localPosition.y, localPosition.z + moveSpeed * DELTA);
    if (Input::Get()->IsKeyPress('S'))
        SetLocalPosition(localPosition.x, localPosition.y, localPosition.z - moveSpeed * DELTA);
    if (Input::Get()->IsKeyPress('A'))
        SetLocalPosition(localPosition.x - moveSpeed * DELTA, localPosition.y, localPosition.z);
    if (Input::Get()->IsKeyPress('D'))
        SetLocalPosition(localPosition.x + moveSpeed * DELTA, localPosition.y, localPosition.z);


    if (localPosition.x < -TILE_SIZE * 0.5f)
        localPosition.x = -TILE_SIZE * 0.5f;
    if (localPosition.x > TILE_SIZE * 1.1f)
        localPosition.x = TILE_SIZE * 1.1f;
    if (localPosition.z < -TILE_SIZE * 0.5f)
        localPosition.z = -TILE_SIZE * 0.5f;
    if (localPosition.z > TILE_SIZE)
        localPosition.z = TILE_SIZE;

    //스크롤로 확대 이런거 하기

     // 부드럽게 보간
    if (!isMatch)
    {
        localPosition.y = GameMath::Lerp(localPosition.y, nextPositionY, DELTA * SMOOTH_SPEED);
        localRotation.x = GameMath::Lerp(localRotation.x, nextRotationX, DELTA * SMOOTH_SPEED);
        if (fabs(localPosition.y - nextPositionY) < EPSILON && fabs(localRotation.x - nextRotationX) < EPSILON)
            isMatch = true;
    }

}

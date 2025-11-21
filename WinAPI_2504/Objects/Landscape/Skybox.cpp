#include "Framework.h"
#include "Skybox.h"

SkyBox::SkyBox(wstring textureFile)
{
	material->SetShader(L"Landscape/Skybox.hlsl");

	//material->SetDiffuseMap(textureFile);
	cubeMap = Texture::Add(textureFile);

	rasterizerStates[0] = new RasterizerState();
	rasterizerStates[1] = new RasterizerState();
	rasterizerStates[1]->FrontCounterClockwise(true);

	depthStencilStates[0] = new DepthStencilState();
	depthStencilStates[1] = new DepthStencilState();
	depthStencilStates[1]->DepthEnable(false);

	buffer = new SkyBuffer();

	SetEvent();
	color = nightColor;
	buffer->Get().color.x = nightColor.x; //저장데이터받을거면수정
	buffer->Get().color.y = nightColor.y; //저장데이터받을거면수정
	buffer->Get().color.z = nightColor.z; //저장데이터받을거면수정
}

SkyBox::~SkyBox()
{
	for (UINT i = 0; i < 2; i++)
		delete rasterizerStates[i];

	for (UINT i = 0; i < 2; i++)
		delete depthStencilStates[i];

	delete buffer;
}

void SkyBox::Render()
{
	buffer->SetPS(5);

	rasterizerStates[1]->SetState();
	depthStencilStates[1]->SetState();

	cubeMap->PSSet(10);
	Sphere::Render();

	rasterizerStates[0]->SetState();
	depthStencilStates[0]->SetState();
}

void SkyBox::Edit()
{
	ImGui::ColorEdit4("WaveColor", (float*)&buffer->Get().color);

}

void SkyBox::Update()
{
	
	angle += (ROTATION_SPEED * DELTA* playSpeed);  // 속도 조절 가능

	buffer->Get().matrix = XMMatrixRotationY(angle);

	UpdateColor();
	//UpdateWorld();
}

void SkyBox::UpdateColor()
{
	if (fabs(buffer->Get().color.x - color.x) > EPSILON ||
		fabs(buffer->Get().color.y - color.y) > EPSILON || fabs(buffer->Get().color.z - color.z) > EPSILON)
	{
		Float4 skyColor = buffer->Get().color;
		Vector3 start = Vector3{ skyColor.x, skyColor.y, skyColor.z };

		start = GameMath::Lerp(start, color, SMOOTH_SPEED * DELTA * playSpeed);
		skyColor.x = start.x;
		skyColor.y = start.y;
		skyColor.z = start.z;

		buffer->Get().color = skyColor;
	}

}

void SkyBox::SetEvent()
{
	EventManager::Get()->AddEvent("SKyOriginColor", [this](void* param) {OriginColor(); });
	EventManager::Get()->AddEvent("SKyNightColor", [this](void* param) {NightColor(); });
	EventManager::Get()->AddEvent("SKySunsetColor", [this](void* param) {SunsetColor(); });
	EventManager::Get()->AddEvent("ChangeSpeed", [this](void* param) {ChangeSpeed(); });
}

void SkyBox::OriginColor()
{
	color = originColor;
}

void SkyBox::NightColor()
{
	color = nightColor;
}

void SkyBox::SunsetColor()
{
	color = sunsetColor;
}

void SkyBox::ChangeSpeed()
{
	playSpeed = 1 / Player::Get()->GetSpeedValue();
}

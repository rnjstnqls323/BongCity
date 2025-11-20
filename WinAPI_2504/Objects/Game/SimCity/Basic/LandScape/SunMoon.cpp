#include "Framework.h"

SunMoon::SunMoon()
{
	CreateLight();
	AddEvent();
}

SunMoon::~SunMoon()
{
	delete buffer;
}

void SunMoon::Update()
{
	MatchSeason();
	UpdateLight();
}

void SunMoon::Render()
{
	buffer->SetPS(1);
}

void SunMoon::Edit()
{
	ImGui::ColorEdit3("AmbientLight", (float*)&buffer->GetData()->ambientLight);
	ImGui::ColorEdit3("AmbientCeil", (float*)&buffer->GetData()->ambientCeil);

	if (ImGui::Button("Add"))
		buffer->GetData()->lightCount++;

	for (UINT i = 0; i < buffer->GetData()->lightCount; i++)
	{
		string name = "Light " + to_string(i);

		if (ImGui::TreeNode(name.c_str()))
		{
			EditLight(buffer->GetData()->lights[i]);
			ImGui::TreePop();
		}
	}
}

void SunMoon::EditLight(LightBuffer::Light& light)
{
	ImGui::Checkbox("Active", (bool*)&light.active);

	const char* items[] = { "Directional", "Point", "Spot", "Capsule" };
	ImGui::Combo("Type", (int*)&light.type, items, IM_ARRAYSIZE(items));

	ImGui::ColorEdit3("Color", (float*)&light.color);
	ImGui::SliderFloat3("Direction", (float*)&light.direction, -1, 1);
	ImGui::DragFloat3("Position", (float*)&light.position);
	ImGui::SliderFloat("Range", &light.range, 0, 500);
	ImGui::SliderFloat("Inner", &light.inner, 0, 180);
	ImGui::SliderFloat("Outer", &light.outer, 0, 180);
	ImGui::DragFloat("Length", &light.length, 0.1f, 10);

}

void SunMoon::CreateLight()
{
	buffer = new LightBuffer();
	buffer->GetData()->lightCount++;

	sun = &buffer->GetData()->lights[buffer->GetData()->lightCount - 2];
	moon = &buffer->GetData()->lights[buffer->GetData()->lightCount - 1];

	season = Player::Get()->GetSeason();
	data = &DataManager::Get()->GetSeasonData((int)season);

	OnMoon(); //이거 세이브데이터 받아올거면 수정해야됨
	linear += (24 - data->nightTime) * correct;
	moon->direction = originDir;
	//nextLightColor = Float4{ 73 / 255 , 81.0f / 255 , 216.0f / 255 , 1 };
}

void SunMoon::OnSun()
{
	moon->active = false;
	sun->color = moon->color;
	nextLightColor = Float4{ 1,1,1,1 };
	embientColor = Vector3{ 215.0f / 255, 95.0f / 255, 22.0f / 255 };
	sun->direction = originDir;
	correct = (float)3 / data->afternoonTime;
	linear = -1;
	nowLight = sun;
	nowLight->active = true;
}

void SunMoon::OnMoon()
{
	sun->active = false;
	moon->color = sun->color;
	nextLightColor = Float4{ 73 / 255 , 81.0f / 255 , 216.0f / 255 , 1 };
	embientColor = Vector3{ 0,0,0 };
	moon->direction = originDir;
	correct = float(3) / (24 - data->afternoonTime);
	linear = -1;
	nowLight = moon;
	nowLight->active = true;
}

void SunMoon::MatchSeason()
{
	if (season != Player::Get()->GetSeason())
	{
		season = Player::Get()->GetSeason();
		data = &DataManager::Get()->GetSeasonData((int)season);
	}
}

void SunMoon::UpdateLight()
{
	float speed = 1 / Player::Get()->GetSpeedValue();
	if (fabs(nowLight->direction.x - linear) > EPSILON)
		nowLight->direction.x = GameMath::Lerp(nowLight->direction.x, linear, DELTA * SMOOTH_VALUE * speed);
		
	
	if(fabs(buffer->GetData()->ambientLight.x - embientColor.x)>EPSILON || 
		fabs(buffer->GetData()->ambientLight.y - embientColor.y) > EPSILON || fabs(buffer->GetData()->ambientLight.z - embientColor.z) > EPSILON)
		buffer->GetData()->ambientLight = GameMath::Lerp(buffer->GetData()->ambientLight, embientColor, SMOOTH_COLOR_VALUE * DELTA * speed);

	if (fabs(nowLight->color.x - nextLightColor.x) > EPSILON)
		nowLight->color.x = GameMath::Lerp(nowLight->color.x, nextLightColor.x, SMOOTH_VALUE * DELTA * speed);
	if(fabs(nowLight->color.y - nextLightColor.y) > EPSILON)
		nowLight->color.y = GameMath::Lerp(nowLight->color.y, nextLightColor.y, SMOOTH_VALUE * DELTA * speed);
	if(fabs(nowLight->color.z - nextLightColor.z) > EPSILON)
		nowLight->color.z = GameMath::Lerp(nowLight->color.z, nextLightColor.z, SMOOTH_VALUE * DELTA * speed);

}

void SunMoon::SunSetEmbient()
{
	embientColor = Vector3{ 215.0f / 255, 95.0f / 255, 22.0f / 255 };
	nextLightColor = Float4{ 153.0f / 255, 136.0f / 255, 117.0f / 255,1 };
}

void SunMoon::OriginEmbient()
{
	embientColor = Vector3{ 221.0f / 255,197.0f / 255,181.0f / 255 };
	nextLightColor = Float4{ 1,1,1,1 };
}

void SunMoon::SetLiner()
{
	linear += correct;
}

void SunMoon::AddEvent()
{
	EventManager::Get()->AddEvent("OnSun", [this](void* param) {OnSun(); });
	EventManager::Get()->AddEvent("OnMoon", [this](void* param) {OnMoon(); });
	EventManager::Get()->AddEvent("SetLinearValue", [this](void* param) {SetLiner(); });
	EventManager::Get()->AddEvent("SunSetEmbient", [this](void* param) {SunSetEmbient(); });
	EventManager::Get()->AddEvent("OriginEmbient", [this](void* param) {OriginEmbient(); });
}

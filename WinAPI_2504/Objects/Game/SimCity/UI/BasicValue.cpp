#include "Framework.h"
#include "BasicValue.h"

BasicValue::BasicValue(Resources resource):resource(resource)
{
	CreateQuad(resource);
	ChangeNumbers(Player::Get()->GetResources(resource));
}

BasicValue::~BasicValue()
{
	delete backGround;
	for (int i = 0; i < MAX_NUM; i++)
	{
		delete numbers[i];
	}
}

void BasicValue::Update()
{
	UpdateWorld();
	if (preValue != Player::Get()->GetResources(resource))
		ChangeNumbers(Player::Get()->GetResources(resource));

	backGround->UpdateWorld();
	for (int i = 0; i < MAX_NUM; i++)
	{
		numbers[i]->UpdateWorld(); //업데이트월드 에딧끝나면 지우기
	}
}

void BasicValue::Render()
{
	backGround->Render();
	for (int i = 0; i < MAX_NUM; i++)
	{
		if (!numbers[i]->IsActive())continue;
		numbers[i]->Render();
	}
}

void BasicValue::CreateQuad(Resources resource)
{
	wstring path = L"Resources/Textures/Simcity/UI/Material/";
	backGround = new Quad( path+ to_wstring((int)resource) + L".png");
	backGround->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
	backGround->SetTag("backGround");
	backGround->SetLocalScale(0.2, 0.15, 1);
	backGround->SetParent(this);

	backGround->UpdateWorld();

	numbers.resize(MAX_NUM);
	float x = -30;
	for (int i = 0; i < MAX_NUM; i++)
	{
		numbers[i] = new Quad(L"Resources/Textures/Simcity/UI/Number/0.png");
		numbers[i]->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
		numbers[i]->SetTag("number"+i);
		numbers[i]->SetLocalScale(0.8, 0.9, 1);
		numbers[i]->SetLocalPosition(x + (20 * i), 0, 0);
		numbers[i]->SetParent(this);

		numbers[i]->UpdateWorld();
	}
}

void BasicValue::ChangeNumbers(int number)
{
	wstring path = L"Resources/Textures/Simcity/UI/Number/";
	int num = 100000;

	preValue = number;

	for (int i = 0; i < MAX_NUM; i++)
	{
		numbers[i]->SetActive(true);

		int value = number / num;

		if (value == 0 && preValue < num && num > 9)
		{
			numbers[i]->SetActive(false);
		}
		else if (value < 0)
		{
			numbers[i]->GetMaterial()->SetDiffuseMap(path + L"0.png");
		}
		else
		{
			numbers[i]->GetMaterial()->SetDiffuseMap(path +to_wstring(value) + L".png");
		}

		number %= num;   
		num /= 10;
	}
}





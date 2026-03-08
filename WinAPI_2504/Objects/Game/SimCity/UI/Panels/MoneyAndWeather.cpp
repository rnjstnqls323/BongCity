#include "Framework.h"
#include "MoneyAndWeather.h"

MoneyAndWeather::MoneyAndWeather()
{
	CreateQuad();
	CreateValue();
	preSeason = Player::Get()->GetSeason();

}

MoneyAndWeather::~MoneyAndWeather()
{
	delete weatherFront;
	delete weatherBackGround;
	for (int i = 0; i < (int)Resources::Max; i++)
	{
		delete values[i];
	}
}

void MoneyAndWeather::Update()
{
	UpdateSeason();
	for (int i = 0; i < (int)Resources::Max; i++)
	{
		values[i]->Update();
	}
}

void MoneyAndWeather::Render()
{
	weatherBackGround->Render();
	weatherFront->Render();

	for (int i = 0; i < (int)Resources::Max; i++)
	{
		values[i]->Render();
	}
}

void MoneyAndWeather::Edit()
{
	for (int i = 0; i < (int)Resources::Max; i++)
	{
		values[i]->Edit();
	}
}


void MoneyAndWeather::CreateQuad()
{
	weatherBackGround = new Quad(L"Resources/Textures/Simcity/UI/Weather/Weather_Back.png");
	weatherBackGround->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
	weatherBackGround->SetLocalPosition(40, 680, 0);
	weatherBackGround->SetTag("weatherBack");
	weatherBackGround->SetLocalScale(0.12f, 0.12f, 1);

	weatherFront = new Quad(L"Resources/Textures/Simcity/UI/Weather/Weather_Front.png");
	weatherFront->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
	weatherFront->SetLocalPosition(40, 680, 0);
	weatherFront->SetTag("weatherFront");
	weatherFront->SetLocalScale(0.12f, 0.12f, 1);

	weatherFront->UpdateWorld();
	weatherBackGround->UpdateWorld();
}

void MoneyAndWeather::CreateValue()
{
	values.resize((int)Resources::Max);
	float x = 170;

	for (int i = 0; i < (int)Resources::Max; i++)
	{
		values[i] = new BasicValue((Resources)i);
		values[i]->SetTag("valueTransform"+i);
		values[i]->SetLocalPosition(x + (i * 180), 680, 0);
	}
}

void MoneyAndWeather::UpdateSeason()
{
	if (preSeason != Player::Get()->GetSeason())
	{
		preSeason = Player::Get()->GetSeason();
		weatherFront->SetLocalRotation(0, 0, weatherFront->GetLocalRotation().z + XMConvertToRadians(-90));
		weatherFront->UpdateWorld();
	}
}

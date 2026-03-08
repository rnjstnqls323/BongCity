#include "Framework.h"

Tree::Tree(Vector2 range, int size, Vector2 noBuildRange, Vector3 pos) :size(size), range(range), noBuildRange(noBuildRange), pos(pos)
{
	CreateTrees();
    season = Player::Get()->GetSeason();
}

Tree::~Tree()
{
	delete material;
	delete vertexBuffer;
}


void Tree::Render()
{
	Environment::Get()->SetAlphaBlend(true);
	Environment::Get()->SetDepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

	vertexBuffer->Set(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
	material->Set();
	geometryShader->Set();

	DC->Draw(size, 0);

	Environment::Get()->SetAlphaBlend(false);
	DC->GSSetShader(nullptr, nullptr, 0);
}

void Tree::Update()
{
    if (season != Player::Get()->GetSeason())
    {
        season = Player::Get()->GetSeason();
        ChangeTrees();
    }
}

void Tree::ChangeTrees()
{
    wstring path = L"Resources/Textures/Landscape/tree";
    material->SetDiffuseMap(path + to_wstring((int)season) + L".png");
}

void Tree::CreateTrees()
{
	material = new Material(L"Geometry/Billboard.hlsl");
	material->SetDiffuseMap(L"Resources/Textures/Landscape/tree0.png");

	geometryShader = Shader::AddGS(L"Geometry/Billboard.hlsl");

	vertices.resize(size);

	for(int i=0;i<size;i++)
	{
		vertices[i].u = GameMath::Random(3.0f, 10.0f);
		vertices[i].v = GameMath::Random(3.0f, 10.0f);

		Vector3 position = GetRandomPos();

		vertices[i].x = position.x;
		vertices[i].y = position.y;
		vertices[i].z = position.z;
	}

	vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexUV), size);
}


Vector3 Tree::GetRandomPos()
{
    Vector3 result = pos;

    // 1) 기본 랜덤 오프셋
    result.x += GameMath::Random(-range.x * 0.5f, range.x * 0.5f);
    result.z += GameMath::Random(-range.y * 0.5f, range.y * 0.5f);

    // 금지구역 사각형 체크
    bool inNoBuild =
        (result.x >= 0 && result.x <= noBuildRange.x) &&
        (result.z >= 0 && result.z <= noBuildRange.y);

    if (inNoBuild)
    {
        // X 처리
        bool evenX = ((int)result.x % 2) == 0;
        if (evenX)
        {
            result.x = GameMath::Random(-range.x * 0.5f, 0.0f);     // 왼쪽
        }
        else
        {
            result.x = GameMath::Random(noBuildRange.x, range.x * 0.5f); // 오른쪽
        }

        // Z 처리
        bool evenZ = ((int)result.z % 2) == 0;
        if (evenZ)
        {
            result.z = GameMath::Random(-range.y * 0.5f, 0.0f);     // 위쪽
        }
        else
        {
            result.z = GameMath::Random(noBuildRange.y, range.y * 0.5f); // 아래쪽
        }
    }


    result.y = 4.0f;
    return result;
}

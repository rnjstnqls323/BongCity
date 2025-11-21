#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct GeometryInput
{
    float4 pos : POSITION0;
    float2 size : SIZE;
    float3 viewPos : POSITION1;
    matrix view : VIEW;
    matrix projection : PROJECTION;
};

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 worldPos : POSITION1;
    float3 viewPos : POSITION0;
};
GeometryInput VS(VertexUV input)
{
    GeometryInput output;
	
    output.pos = input.pos;
    output.size = input.uv;
    output.viewPos = invView._41_42_43;
    output.view = view;
    output.projection = projection;
	
    return output;
}

static const float2 TEXCOORD[4] =
{
    float2(0.0f, 1.0f),
	float2(0.0f, 0.0f),
	float2(1.0f, 1.0f),
	float2(1.0f, 0.0f)
};

[maxvertexcount(4)]
void GS(point GeometryInput input[1], inout TriangleStream<PixelInput> output)
{
    float3 up = float3(0, 1, 0);

    // 카메라 방향 normal
    float3 camDir = normalize(input[0].viewPos - input[0].pos.xyz);
    float3 normal = -camDir;

    float3 right = normalize(cross(up, normal));
    float2 halfSize = input[0].size * 0.5f;

    float4 vertices[4];
    vertices[0] = float4(input[0].pos.xyz - right * halfSize.x - up * halfSize.y, 1.0f);
    vertices[1] = float4(input[0].pos.xyz - right * halfSize.x + up * halfSize.y, 1.0f);
    vertices[2] = float4(input[0].pos.xyz + right * halfSize.x - up * halfSize.y, 1.0f);
    vertices[3] = float4(input[0].pos.xyz + right * halfSize.x + up * halfSize.y, 1.0f);

    PixelInput element;

    [unroll]
    for (uint i = 0; i < 4; i++)
    {
        float4 worldPos = vertices[i];

        element.worldPos = worldPos.xyz;

        // 뷰/프로젝션 한 번씩
        float4 viewPos = mul(worldPos, input[0].view);
        element.pos = mul(viewPos, input[0].projection);
        element.viewPos = viewPos.xyz;

        element.normal = -normal;
        element.uv = TEXCOORD[i];

        output.Append(element);
    }
}


float4 PS(PixelInput input) : SV_TARGET
{
    Material material;
    material.diffuseColor = diffuseMap.Sample(samplerState, input.uv);
    material.specularIntensity = float4(1, 1, 1, 1);
    material.normal = normalize(input.normal);
    material.worldPos = input.worldPos;
    material.viewPos = input.viewPos;

    float4 result = CalcAmbient(material);

    [unroll]
    for (uint i = 0; i < lightCount; i++)
    {
        if (!lights[i].active)
            continue;

        if (lights[i].type == 0)
            result += CalcDirectional(material, lights[i]);
        else if (lights[i].type == 1)
            result += CalcPoint(material, lights[i]);
        else if (lights[i].type == 2)
            result += CalcSpot(material, lights[i]);
    }

    return result;
}


#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct PixelInput
{
    float4 pos : SV_POSITION;
    float3 originPos : POSITION;
};

cbuffer SkyBuffer : register(b5)
{
    float4 color;
    matrix skyView;
}

PixelInput VS(VertexUV input)
{
    PixelInput output;
    output.pos.xyz = mul(input.pos.xyz, (float3x3) view);
    output.pos.w = 1.0f;
    output.pos = mul(output.pos, projection);

    output.originPos = input.pos.xyz;
	
    return output;
}

TextureCube cubeMap : register(t10);

float4 PS(PixelInput input) : SV_TARGET
{
    float3 rotatedDir = mul(input.originPos, (float3x3) skyView);

    float3 skyColor = cubeMap.Sample(samplerState, rotatedDir).rgb;

    return float4(skyColor, 1.0f) * color;
}
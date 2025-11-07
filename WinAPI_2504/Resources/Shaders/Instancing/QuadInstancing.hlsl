#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct VertexInput
{
    float4 pos : POSITION;
    float2 uv : UV;

    matrix transform : INSTANCE_TRANSFORM;
    float4 color : INSTANCE_COLOR;
};
struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;

    float3 viewPos : POSITION0;
    float3 worldPos : POSITION1;
    
    float4 color : COLOR;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.pos = mul(input.pos, input.transform);
    
    output.worldPos = output.pos;
    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.uv = input.uv;

    output.viewPos = invView._41_42_43;
    
    output.color = input.color;
    
    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 baseColor = diffuseMap.Sample(samplerState, input.uv) * input.color;
    return baseColor;
}
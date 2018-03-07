struct outPut
{
    float4 positions : SV_POSITION;
    float3 UVcoordinates : UV;
    float3 norms : NORMAL;
};

cbuffer Light : register(b1)
{
    float4 pos;
    float4 col;
    float4 dir;
};

Texture2D skin : register(t0);

SamplerState sState : register(s0);


float3 main(outPut headingOut) : SV_TARGET
{
    float3 direction = dir.xyz;
    //float4 lPos = pos;
    float4 skinColor;
    skinColor = skin.Sample(sState, float2(headingOut.UVcoordinates.x, headingOut.UVcoordinates.y));

    direction = normalize(direction);

    //trying to calculate point light
    //float lightDir = normalize(lPos - )

    //calculating directional lighting
    float lightRat = saturate(dot(-direction, headingOut.norms));
    headingOut.UVcoordinates = lightRat * col * skinColor;

    return headingOut.UVcoordinates;
}
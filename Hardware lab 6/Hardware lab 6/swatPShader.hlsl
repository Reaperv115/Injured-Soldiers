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
    float4 skinColor;
    skinColor = skin.Sample(sState, headingOut.UVcoordinates.xy);

    direction = normalize(direction);

    //calculating the lighting
    float lightRat = saturate(dot(-direction, headingOut.norms));
    float4 result = lightRat * col * skinColor;
    //headingOut.UVcoordinates = lightRat * col * headingOut.UVcoordinates;
    
    //headingOut.UVcoordinates = skinColor;

    return result;
}
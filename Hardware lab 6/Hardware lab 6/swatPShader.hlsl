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

cbuffer theMatrices : register(b2)
{
    float4x4 CUBEworldMat;
    float4x4 SWATworldMat;
    float4x4 perspectiveMat;
    float4x4 viewMat;
    float4x4 projection;
    float4x4 cam;
};

Texture2D skin : register(t0);

SamplerState sState : register(s0);


float3 main(outPut headingOut) : SV_TARGET
{
    float3 direction = dir.xyz;
    float4 skinColor;
    skinColor = skin.Sample(sState, float2(headingOut.UVcoordinates.x, headingOut.UVcoordinates.y));

    direction = normalize(direction);


    //calculating directional lighting
    float DlightRat = saturate(dot(-direction, headingOut.norms));
    headingOut.UVcoordinates = DlightRat * col * skinColor;

    return headingOut.UVcoordinates;
}
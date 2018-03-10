struct outPut
{
    float4 positions : SV_POSITION;
    float3 UVcoordinates : UV;
    float3 norms : NORMAL;
};

cbuffer DLight : register(b2)
{
    float4 Dpos;
    float4 Dcol;
    float4 Ddir;
};

cbuffer theMatrices : register(b2)
{
    float4x4 CUBEworldMat;
    float4x4 SWATworldMat;
    float4x4 PILLARworldMat;
    float4x4 GRIDworldMat;
    float4x4 perspectiveMat;
    float4x4 viewMat;
    float4x4 projection;
    float4x4 cam;
};

Texture2D skin : register(t0);

SamplerState sState : register(s0);


float4 main(outPut headingOut) : SV_TARGET
{
    float3 direction = Ddir.xyz;
    float4 skinColor;
    skinColor = skin.Sample(sState, headingOut.UVcoordinates.xy);

    direction = normalize(direction);


    //calculating directional lighting
    float DlightRat = saturate(dot(-direction, headingOut.norms));
    float4 color = DlightRat * Dcol * skinColor;

    return color;
}
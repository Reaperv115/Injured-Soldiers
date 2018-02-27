struct outPut
{
    float4 positions : SV_POSITION;
    float4 UVcoordinates : UV;
    float4 norms : NORMAL;
    float2 text : TEXTURE;
};

Texture2D skin : register(t0);

SamplerState sState : register(s0);


float3 main(outPut headingOut, float2 bUV : TEXTURE) : SV_TARGET
{
    float4 skinColor;
    skinColor = skin.Sample(sState, bUV);

    headingOut.UVcoordinates = skinColor;

    return headingOut.UVcoordinates;
}
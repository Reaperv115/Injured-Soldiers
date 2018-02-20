struct outPut
{
    float4 positions : SV_POSITION;
    float4 UVcoordinates : UV;
    float4 norms : NORMAL;
};

cbuffer theLight : register(b0)
{
    float3 pos : SPOT;
    float3 color : COLOR;
    float4 dir : DIRECTION;
}


float4 main(outPut headingOut) : SV_TARGET
{
    float lightRat = saturate(dot(-dir.xyzw, headingOut.norms));
    headingOut.UVcoordinates = lightRat * headingOut.UVcoordinates;

    return headingOut.UVcoordinates;
}
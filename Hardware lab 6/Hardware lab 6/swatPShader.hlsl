struct outPut
{
    float4 positions : SV_POSITION;
    float4 UVcoordinates : UV;
    float4 norms : NORMAL;
};


float3 main(outPut headingOut) : SV_TARGET
{
    return headingOut.UVcoordinates;
}
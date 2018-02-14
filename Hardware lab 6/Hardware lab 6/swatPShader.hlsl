struct outPut
{
    float4 positions : SV_POSITION;
    float4 UVcoordinates : UV;
    float3 norms : NORMAL;
};


float4 main(outPut headingOut) : SV_TARGET
{
    return headingOut.UVcoordinates;

	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}
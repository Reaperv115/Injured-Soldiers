struct outPut
{
    float4 positions : LOCATION;
    float4 UVcoordinates : UV;
    float3 norms : NORMAL;
};


outPut main(outPut headingOut) : SV_TARGET
{
    return headingOut;

	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}
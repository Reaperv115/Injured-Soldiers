
struct theOutput
{
    float4 projectedPos : SV_POSITION; 
    float4 outgoingCol : RGBVal; //color coming in from vertex shader
    float3 normal : theNORMAL;
    float3 dir : dir;
};

cbuffer theLight : register(b0)
{
	float3 vec; //vector of the light
	float4 lColor; //color of the light
}

cbuffer Cube : register(b1)
{
	float4 cColor; //color of the surface
    float3 norm;
}


float4 main(theOutput bringIn) : SV_TARGET
{
    float4 cubeColor = cColor;
    //float4 lightColor = lColor;

    //float lightRat = saturate(dot(-vec.xyz, bringIn.normal));
    //cubeColor = lightRat * lightColor * cubeColor;
    //bringIn.outgoingCol = bringIn.outgoingCol;
    bringIn.outgoingCol = cubeColor;

    return bringIn.outgoingCol;
	//return colorFromRasterizer;
}

struct theOutput
{
    float4 projectedPos : POSITION; 
    float4 outgoingCol : RGBVal; //color coming in from vertex shader
    float3 normal : theNORMAL;
    float3 dir : dir;
};

//cbuffer Cube : register(b1)
//{
//	float4 cColor; //color of the surface
//}


theOutput main(theOutput bringIn) : SV_TARGET
{
    //float4 cubeColor = cColor;

   
    //bringIn.outgoingCol = cubeColor;

    return bringIn;
}
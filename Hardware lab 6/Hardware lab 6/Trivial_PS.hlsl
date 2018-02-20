
struct theOutput
{
    float4 projectedPos : SV_POSITION; 
    float4 outgoingCol : RGBVal; //color coming in from vertex shader
    float3 normal : theNORMAL;
    float3 dir : dir;
};


float4 main(theOutput bringIn) : SV_TARGET
{
    return bringIn.projectedPos;
}
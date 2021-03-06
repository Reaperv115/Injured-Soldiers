
struct theOutput
{
    float4 projectedPos : SV_POSITION; 
    float4 outgoingCol : RGBVal; //color coming in from vertex shader
    float3 normal : theNORMAL;
    float3 dir : dir;
    float3 lsPos : POSITION;
};

TextureCube textedCube : register(t1);
SamplerState sampState : register(s1);

float4 main(theOutput bringIn) : SV_TARGET
{
    float4 cColor = textedCube.Sample(sampState, bringIn.lsPos);
    bringIn.projectedPos = cColor;

    return bringIn.projectedPos;
}
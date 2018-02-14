struct outPut
{
    float4 thePos : SV_POSITION;
    float4 pigment : UV;
    float3 norms : NORMAL;
};

struct inPut
{
    float4 coords : LOCATION;
    float4 coloration : UV;
    float3 normals : NORMAL;
};


outPut main(inPut fromBuffer)
{
    outPut toPixelShader;
    

    toPixelShader.thePos = fromBuffer.coords;
    toPixelShader.pigment = fromBuffer.coloration;
    toPixelShader.norms = fromBuffer.normals;

    return toPixelShader;
}
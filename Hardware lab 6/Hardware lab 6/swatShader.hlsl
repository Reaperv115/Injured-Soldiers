struct outPut
{
    float4 thePos : POSITION;
    float4 pigment : UV;
    float4 norms : NORMAL;
};

struct inPut
{
    float4 coords : POSITION;
    float4 coloration : UV;
    float4 normals : NORMAL;
};

outPut main(/*float4 pos : POSITION*/inPut fromBuffer)
{
    outPut toPixelShader;

    fromBuffer.coords = toPixelShader.thePos;
    fromBuffer.coloration = toPixelShader.pigment;
    fromBuffer.normals = toPixelShader.norms;

    return toPixelShader;
}
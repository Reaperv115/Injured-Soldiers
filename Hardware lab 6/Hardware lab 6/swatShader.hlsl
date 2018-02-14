
#pragma pack_matrix(row_major)
struct outPut
{
    float4 thePos : SV_POSITION;
    float4 pigment : UV;
    float3 norms : NORMAL;
};

struct inPut
{
    float4 coords : POSITION;
    float4 coloration : UV;
    float3 normals : NORMAL;
};

cbuffer theMatrices : register(b2)
{
    float4x4 worldMat;
    float4x4 perspectiveMat;
    float4x4 viewMat;
    float4x4 projection;
    float4x4 cam;
};


outPut main(inPut fromBuffer)
{
    outPut toPixelShader = (outPut)0;
    fromBuffer.coords.w = 1;

    fromBuffer.coords = mul(fromBuffer.coords, worldMat);
    fromBuffer.coords = mul(fromBuffer.coords, viewMat);
    fromBuffer.coords = mul(fromBuffer.coords, perspectiveMat);

    toPixelShader.thePos.x = fromBuffer.coords.x;
    toPixelShader.thePos.y = fromBuffer.coords.y;
    toPixelShader.thePos.z = fromBuffer.coords.z;
    toPixelShader.thePos.w = fromBuffer.coords.w;

    //toPixelShader.thePos = fromBuffer.coords;
    //toPixelShader.pigment = fromBuffer.coloration;
    //toPixelShader.norms = fromBuffer.normals;

    return toPixelShader;
}
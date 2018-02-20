
#pragma pack_matrix(row_major)
struct outPut
{
    float4 thePos : SV_POSITION;
    float4 pigment : UV;
    float4 norms : NORMAL;
};

struct inPut
{
    float4 coords : LOCATION;
    float4 coloration : UV;
    float4 normals : NORMAL;
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

    //the coordiantes going through space
    fromBuffer.coords = mul(fromBuffer.coords, worldMat);
    fromBuffer.coords = mul(fromBuffer.coords, viewMat);
    fromBuffer.coords = mul(fromBuffer.coords, perspectiveMat);

    //the nromals going through space
    fromBuffer.normals = mul(fromBuffer.normals, worldMat);
    fromBuffer.normals = mul(fromBuffer.normals, viewMat);
    fromBuffer.normals = mul(fromBuffer.normals, perspectiveMat);

    //equality for all
    toPixelShader.thePos.x = fromBuffer.coords.x;
    toPixelShader.thePos.y = fromBuffer.coords.y;
    toPixelShader.thePos.z = fromBuffer.coords.z;
    toPixelShader.thePos.w = fromBuffer.coords.w;
    toPixelShader.norms = fromBuffer.normals;

    //back to the motherland
    return toPixelShader;
}
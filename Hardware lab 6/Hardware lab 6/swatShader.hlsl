
#pragma pack_matrix(row_major)
struct outPut
{
    float4 thePos : SV_POSITION;
    float3 textCoord : UV;
    float3 norms : NORMAL;
};

struct inPut
{
    float3 coords : LOCATION;
    float3 textcoordinates : UV;
    float3 normals : NORMAL;
};

cbuffer theMatrices : register(b2)
{
    float4x4 CUBEworldMat;
    float4x4 SWATworldMat;
    float4x4 perspectiveMat;
    float4x4 viewMat;
    float4x4 projection;
    float4x4 cam;
};




outPut main(inPut fromBuffer)
{
    outPut toPixelShader = (outPut)0;
    float4 temp = float4(fromBuffer.coords, 1);
    temp.w = 1;

    //the coordiantes going through space
    temp = mul(temp, SWATworldMat);
    temp = mul(temp, viewMat);
    temp = mul(temp, perspectiveMat);

    //the normals going through space
    fromBuffer.normals = mul(fromBuffer.normals, (float3x3)SWATworldMat);

    //normalizing the normals
    fromBuffer.normals = normalize(fromBuffer.normals);

    toPixelShader.norms = fromBuffer.normals;

    //equality for all
    toPixelShader.thePos.x = temp.x;
    toPixelShader.thePos.y = temp.y;
    toPixelShader.thePos.z = temp.z;
    toPixelShader.thePos.w = temp.w;
  
    toPixelShader.textCoord = fromBuffer.textcoordinates;

    //back to the motherland
    return toPixelShader;
}
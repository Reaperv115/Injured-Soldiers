
#pragma pack_matrix(row_major)
struct outPut
{
    float4 thePos : SV_POSITION;
    float4 pigment : UV;
    float4 norms : NORMAL;
};

struct inPut
{
    float3 coords : LOCATION;
    float3 coloration : UV;
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

cbuffer Light : register(b1)
{
    float4 pos;
    float4 col;
    float4 dir;
};


outPut main(inPut fromBuffer)
{
    outPut toPixelShader = (outPut)0;
    float4 temp = float4(fromBuffer.coords, 1);
    temp.w = 1;

    //the coordiantes going through space
    temp = mul(temp, worldMat);
    temp = mul(temp, viewMat);
    temp = mul(temp, perspectiveMat);

    //the normals going through space
    fromBuffer.normals = mul(fromBuffer.normals, worldMat);

    //normalizing the normals
    fromBuffer.normals = normalize(fromBuffer.normals);

    //calculating the lighting
    float lightRat = saturate(dot(-dir.xyz, fromBuffer.normals));
    fromBuffer.coloration = lightRat * col;

    //equality for all
    toPixelShader.thePos.x = temp.x;
    toPixelShader.thePos.y = temp.y;
    toPixelShader.thePos.z = temp.z;
    toPixelShader.thePos.w = temp.w;
    //toPixelShader.norms = fromBuffer.normals;
    toPixelShader.pigment = float4(fromBuffer.coloration, 1.0f);

    //back to the motherland
    return toPixelShader;
}
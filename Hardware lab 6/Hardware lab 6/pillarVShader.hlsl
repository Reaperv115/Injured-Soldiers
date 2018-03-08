
#pragma pack_matrix(row_major)
struct outPut
{
    float4 pos : SV_POSITION;
    float3 texcoord : UV;
    float3 normals : NORMALS;
};

struct inPut
{
    float3 coord : LOCATION;
    float3 textrcoords : UV;
    float3 normals : NORMALS;
};

cbuffer theMatrices : register(b2)
{
    float4x4 CUBEworldMat;
    float4x4 SWATworldMat;
    float4x4 PILLARworldMat;
    float4x4 perspectiveMat;
    float4x4 viewMat;
    float4x4 projection;
    float4x4 cam;
};

outPut main( inPut frombuff )
{
    outPut toPixelshader = (outPut)0;
    float4 temp = float4(frombuff.coord, 1);
    temp.w = 1;

    temp = mul(temp, PILLARworldMat);
    temp = mul(temp, viewMat);
    temp = mul(temp, perspectiveMat);

    frombuff.normals = mul(frombuff.normals, (float3x3)PILLARworldMat);

    frombuff.normals = normalize(frombuff.normals);

    toPixelshader.normals = frombuff.normals;

    toPixelshader.pos.x = temp.x;
    toPixelshader.pos.y = temp.y;
    toPixelshader.pos.z = temp.z;
    toPixelshader.pos.w = temp.w;

    toPixelshader.texcoord = frombuff.textrcoords;


    return toPixelshader;

	//return pos;
}
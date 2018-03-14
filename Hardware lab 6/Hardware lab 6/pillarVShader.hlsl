
#pragma pack_matrix(row_major)
struct outPut
{
    float4 pos : SV_POSITION;
    float3 texcoord : UV;
    float3 normals : NORMALS;
    float3 wPos : WORLD;
};

struct inPut
{
    float3 coord : LOCATION;
    float3 textrcoords : UV;
    float3 normals : NORMALS;
};

cbuffer theMatrices : register(b2)
{
    float4x4 WorldArray[2];
    float4x4 perspectiveMat;
    float4x4 viewMat;
};

outPut main(inPut frombuff)
{
    outPut toPixelshader = (outPut)0;
    float4 tmp = float4(frombuff.coord, 1);
    tmp.w = 1;

    tmp = mul(tmp, WorldArray[0]);
    toPixelshader.wPos = tmp.xyz;
    tmp = mul(tmp, viewMat);
    tmp = mul(tmp, perspectiveMat);

    frombuff.normals = mul(frombuff.normals, (float3x3)WorldArray[0]);

    frombuff.normals = normalize(frombuff.normals);

    toPixelshader.normals = frombuff.normals;

    toPixelshader.pos.x = tmp.x;
    toPixelshader.pos.y = tmp.y;
    toPixelshader.pos.z = tmp.z;
    toPixelshader.pos.w = tmp.w;

    toPixelshader.texcoord = frombuff.textrcoords;


    return toPixelshader;
}
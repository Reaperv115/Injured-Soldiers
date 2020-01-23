#pragma pack_matrix(row_major)


struct VS_IN
{
    float3 pos : POSITION;
};

struct VS_OUT
{
    float4 position : SV_POSITION;
};

cbuffer theMatrices : register(b2)
{
    float4x4 WorldArray[2];
    float4x4 perspectiveMat;
    float4x4 viewMat;
};

VS_OUT main(VS_IN comingIn)
{
    VS_OUT leaving = (VS_OUT) 0;
    float4 tmp = float4(comingIn.pos, 1.0f);
    tmp.w = 1;

    tmp = mul(tmp, WorldArray[0]);
    tmp = mul(tmp, viewMat);
    tmp = mul(tmp, perspectiveMat);

    leaving.position.x = tmp.x;
    leaving.position.y = tmp.y;
    leaving.position.z = tmp.z;
    leaving.position.w = tmp.w;


    return leaving;
}
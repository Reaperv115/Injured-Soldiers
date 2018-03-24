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

    comingIn.pos = mul(comingIn.pos, WorldArray[0]);
    comingIn.pos = mul(comingIn.pos, viewMat);
    comingIn.pos = mul(comingIn.pos, perspectiveMat);


    return leaving;
}
#pragma pack_matrix(row_major)

struct Input
{
    float4 pos : POSITION;
    float4 col : COLOR;
};

struct Output
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

cbuffer theMatrices : register(b2)
{
    float4x4 WorldArray[2];
    float4x4 perspectiveMat;
    float4x4 viewMat;
};


Output main(Input comingIn)
{
    Output goingOut;

    comingIn.pos = mul(comingIn.pos, WorldArray[0]);

    goingOut.pos = comingIn.pos;
    goingOut.color = comingIn.col;

    


    return goingOut;
}
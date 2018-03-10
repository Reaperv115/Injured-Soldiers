#pragma pack_matrix(row_major)

struct outPut
{
    float4 coords : SV_POSITION;
    float3 textCoords : COLOR;
};

struct inPut
{
    float3 projectedCoords : POSITION;
    float4 color : COLOR;
};

cbuffer theMatrices : register(b2)
{
    float4x4 CUBEworldMat;
    float4x4 SWATworldMat;
    float4x4 PILLARworldMat;
    float4x4 GRIDworldMat;
    float4x4 perspectiveMat;
    float4x4 viewMat;
    float4x4 projection;
    float4x4 cam;
};

outPut main(inPut comingIn)
{
    outPut toPShader = (outPut) 0;

    float4 tmp = float4(comingIn.projectedCoords, 1);
    tmp.w = 1;

    tmp = mul(tmp, GRIDworldMat);
    tmp - mul(tmp, viewMat);
    tmp = mul(tmp, perspectiveMat);

    toPShader.coords.x = tmp.x;
    toPShader.coords.y = tmp.y;
    toPShader.coords.z = tmp.z;
    toPShader.coords.w = tmp.w;

    return toPShader;

	//return pos;
}

struct outPut
{
    float4 pos : SV_POSITION;
    float3 uvs : COLOR;
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

float4 main(outPut takenOut) : SV_TARGET
{

    return float4(takenOut.uvs, 1);

	//turn float4(1.0f, 1.0f, 1.0f, 1.0f);
}
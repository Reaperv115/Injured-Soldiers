struct outPut
{
    float4 position : SV_POSITION;
    float3 uv : UV;
    float3 normals : NORMAL;
};

cbuffer Light : register(b1)
{
    float4 pos;
    float4 col;
    float4 dir;
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

Texture2D skin : register(t0);
SamplerState sState : register(s0);

float3 main(outPut goingOut) : SV_TARGET
{
    //float3 direction = dir.xyz;
    //float4 sColor;
    //sColor = skin.Sample(sState, float2(goingOut.uv.x, goingOut.uv.y));
    //direction = normalize(direction);

    //float lightRat = normalize()

    return goingOut.uv;

	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}
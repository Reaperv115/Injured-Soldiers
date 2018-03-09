struct outPut
{
    float4 position : SV_POSITION;
    float3 uv : UV;
    float3 normals : NORMALS;
    float3 wPos : WORLD;

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
    float4x4 PILLARworldMat;
    //float4x4 GRIDworldMat;
    float4x4 perspectiveMat;
    float4x4 viewMat;
    float4x4 projection;
    float4x4 cam;
};

Texture2D skin : register(t0);
SamplerState sState : register(s0);

float3 main(outPut goingOut) : SV_TARGET
{
    int lightRadius = 30;
    float3 direction = dir.xyz;
    float4 sColor;
    sColor = skin.Sample(sState, goingOut.uv.xy);
    direction = normalize(direction);

    float attenuation = pow(1.0f - saturate(length(pos - goingOut.wPos) / lightRadius), 2);

    float lightDir = normalize(pos - goingOut.wPos);
    float lightRat = saturate(dot(direction, goingOut.normals));
    float light = lightRat * col;
    goingOut.uv = goingOut.uv * attenuation + light;

    return sColor;

	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}
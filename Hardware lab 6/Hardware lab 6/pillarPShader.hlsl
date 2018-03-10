struct outPut
{
    float4 position : SV_POSITION;
    float3 uv : UV;
    float3 normals : NORMALS;
    float3 wPos : WORLD;

};

cbuffer PLight : register(b1)
{
    float4 Ppos;
    float4 Pcol;
    float4 Pdir;
};

cbuffer SLight : register(b3)
{
    float4 Spos;
    float4 Scol;
    float4 Sdir;
}


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

Texture2D skin : register(t0);
SamplerState sState : register(s0);

float4 main(outPut goingOut) : SV_TARGET
{
    float lightRadius = 6;
    float3 direction = Pdir.xyz;
    float4 sColor;
    sColor = skin.Sample(sState, goingOut.uv.xy);
    direction = normalize(direction);

    float attenuation = 1.0f - saturate(length(Ppos.xyz - goingOut.wPos.xyz) / lightRadius); //, 2);

    float3 lightDir = normalize(Ppos - goingOut.wPos);
    float lightRat = saturate(dot(lightDir, goingOut.normals));
    float4 light = lightRat * Pcol * sColor * attenuation;
    //goingOut.uv = goingOut.uv * attenuation * light;

    return light;

	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}
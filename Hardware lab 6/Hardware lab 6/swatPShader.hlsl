struct outPut
{
    float4 positions : SV_POSITION;
    float3 UVcoordinates : UV;
    float3 norms : NORMAL;
    float3 wPos : WORLD;
};

cbuffer DLight : register(b2)
{
    float4 Dpos;
    float4 Dcol;
    float4 Ddir;
};

cbuffer SLight : register(b3)
{
    float4 sPos;
    float4 Scol;
    float4 sDir;
    float4 scDir;
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


float4 main(outPut headingOut) : SV_TARGET
{
    float3 direction = Ddir.xyz;
    float3 sdir = sDir;
    float4 pos = sPos;
    float lightRadius = 6;

    float4 skinColor;
    skinColor = skin.Sample(sState, headingOut.UVcoordinates.xy);

    direction = normalize(direction);

    float attenuation = 1.0f - saturate(length(sPos.xyz - headingOut.wPos.xyz) / lightRadius);

    float3 lightDir = normalize(pos - headingOut.wPos);
    float surfRat = saturate(dot(-sdir, scDir));
    float spotFact = (surfRat > scDir) ? 1 : 0;
    float Slightrat = saturate(dot(sDir, headingOut.norms));


    //calculating directional lighting
    float DlightRat = saturate(dot(-direction, headingOut.norms));
    float4 color = DlightRat * Dcol * skinColor * spotFact * Slightrat * Scol * skinColor * attenuation;

    return color;
}
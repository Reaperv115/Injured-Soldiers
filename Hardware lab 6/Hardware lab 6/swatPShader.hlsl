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
    float3 sDir;
    float inner;
    float3 scDir;
    float outter;
    float3 padding;
    float fallOff;
}

cbuffer theMatrices : register(b2)
{
    float4x4 CUBEworldMat;
    float4x4 SWATworldMat[2];
    float4x4 PILLARworldMat;
    //float4x4 GRIDworldMat;
    float4x4 perspectiveMat;
    float4x4 viewMat;
    //float4x4 projection;
    //float4x4 cam;
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
    float nVec = pos - headingOut.positions;
    float innerVec = dot(inner, nVec);
    float outterVec = dot(outter, nVec);
    direction = normalize(direction);

    //float attenuation = 1.0f - saturate(length(sPos - headingOut.wPos) / lightRadius);
    

    //calculating spot lighting
    float3 lightDir = normalize(pos.xyz - headingOut.wPos);
    float surfRat = saturate(dot(-lightDir, normalize(sDir)));
    float spotFact = (surfRat > 0.80f) ? 1 : 0;
    float Slightrat = saturate(dot(lightDir, normalize(headingOut.norms)));
    float attenuation = 1.0f - saturate((0.95f - surfRat) / (0.95f - 0.80f));

    //calculating directional lighting
    float DlightRat = saturate(dot(-direction, headingOut.norms));

    //color of object after directional lighting
    float4 Dcolor = DlightRat * Dcol;

    //color of object after spot lighting
    float4 Scolor = spotFact * Slightrat * Scol * skinColor * attenuation;
    
    float4 color = saturate(Dcolor + Scolor);

    return color;
}
struct outPut
{
    float4 position : SV_POSITION;
    float3 uv : UV;
    float3 normals : NORMALS;
    float3 wPos : WORLD;
    //float3 otherworldPos;
    //float3 viewDirection : TEXCOORD1;
};

cbuffer PLight : register(b1)
{
    float4 Ppos;
    float4 Pcol;
    float4 Pdir;
};

cbuffer Cam : register(b4)
{
    float4 campos;
}


cbuffer theMatrices : register(b2)
{
    float4x4 WorldArray[2];
    float4x4 perspectiveMat;
    float4x4 viewMat;
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

    //specular lighting stuff
    int specularPow = 2;
    float lightIntensity = 0.1f;
    //lightIntensity = saturate(dot(goingOut.normals, -direction));

    float attenuation = 1.0f - saturate(length(Ppos.xyz - goingOut.wPos.xyz) / lightRadius);

    //specular lighting
    float3 viewDir = normalize(goingOut.wPos - Ppos);
    float3 reflection = reflect(viewDir, goingOut.normals);
    float3 toCam = normalize(campos - goingOut.wPos);
    float spec = saturate(dot(reflection, toCam));
    spec = pow(spec, specularPow);
    //float intensity = max(pow(saturate(dot(goingOut.normals, normalize(halfVec))), specularPow), 0);

    //point lighting stuff
    float3 lightDir = normalize(Ppos - goingOut.wPos);
    float lightRat = saturate(dot(lightDir, goingOut.normals));
    float4 light = lightRat * Pcol * sColor * attenuation/* * spec * lightIntensity*/;

    //float4 lightResult = col * lightIntensity * intensity;

    return light;
}
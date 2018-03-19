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

//cbuffer SLight : register(b3)
//{
//    float4 Spos;
//    float4 Scol;
//    float4 Sdir;
//}

cbuffer specLight : register(b4)
{
    float4 pos, col;
    float3 dir;
    float padding;
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

    int specularPow = 4;
    //float3 reflection;
    //float4 specular;
    float lightIntensity;
    //specular = float4(0.0f, 0.0f, 0.0f, 0.0f);
    lightIntensity = saturate(dot(goingOut.normals, -direction));
    
    //if(lightIntensity > 0.0f)
    //{
    //    sColor = saturate(sColor);

    //    reflection = normalize(2 * lightIntensity * goingOut.normals - (-direction));
    //    specular = pow(saturate(dot(reflection, goingOut.viewDirection)), specularPow);

    //}

    //sColor = sColor * goingOut.uv.xy;

    //sColor = saturate(sColor + specular);

    float attenuation = 1.0f - saturate(length(Ppos.xyz - goingOut.wPos.xyz) / lightRadius);

    //float4 camworldPos = mul(viewMat, WorldArray[0]);

    //specular lighting
    //float3 viewDir = normalize(goingOut.otherworldPos - goingOut.position.xyz);
    //float3 halfVec = normalize((-dir) + viewDir);
    //float intensity = max(pow(saturate(dot(goingOut.normals, normalize(halfVec))), specularPow), 0);

    float3 lightDir = normalize(Ppos - goingOut.wPos);
    float lightRat = saturate(dot(lightDir, goingOut.normals));
    float4 light = lightRat * Pcol * sColor * attenuation;

    //float4 lightResult = col * lightIntensity * intensity;

    return light;
}
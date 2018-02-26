struct outPut
{
    float4 positions : SV_POSITION;
    float4 UVcoordinates : UV;
    float4 norms : NORMAL;
    float2 text : TEXTURE;
};

cbuffer flesh : register(b1)
{
    float2 uv;
}

Texture2D skin;
SamplerState sState;


float3 main(outPut headingOut) : SV_TARGET
{
    float4 textColor;

    //textColor = skin.Sample(sState, headingOut.text);

    //headingOut.UVcoordinates = textColor;

    return headingOut.UVcoordinates;
}
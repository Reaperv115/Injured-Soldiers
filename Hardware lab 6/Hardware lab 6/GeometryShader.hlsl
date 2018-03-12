struct GSOutput
{
	float4 pos : SV_POSITION;
    float3 col : UV;
    float3 norm : NORMAL;
};

struct GSInput
{
    float3 coords : LOCATION;
    float3 uvc : UV;
    float3 norm : NORMAL;
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

[maxvertexcount(3)]
void main(line GSInput input[2] : SV_POSITION, inout TriangleStream< GSOutput > output)
{
    GSOutput verts[3] =
    {
        float4(1, 0, 0, 1), float3(0, 0, 0), float3(0.0f, 0.0f, -1.0f),
        float4(0, 1, 0, 1), float3(0, 0, 0), float3(0.0f, 0.0f, -1.0f),
        float4(0, 0, 1, 1), float3(0, 0, 0), float3(0.0f, 0.0f, -1.0f),
    };


    //bottom left
    verts[0].pos.xyz = input[0].coords.xyz;
    verts[0].pos.x -= 0.5f;

    //bottom right
    verts[2].pos = verts[0].pos;
    verts[2].pos.x += 1.0f;

    //top center
    verts[1].pos.xyz = input[1].coords.xyz;

    //float4x4 mVp = mul(viewMat, perspectiveMat);

    //for (uint i = 0; i < 3; ++i)
    //{
    //    verts[i].pos = mul(verts[i].pos, SWATworldMat);
    //    verts[i].pos = mul(verts[i].pos, mVp);
    //    verts[i].pos = mul(verts[i].pos, perspectiveMat);
    //}

    output.Append(verts[0]);
    output.Append(verts[1]);
    output.Append(verts[2]);

	//for (uint i = 0; i < 2; i++)
	//{
	//	GSOutput element;
	//	element.pos = input[i];
	//	output.Append(element);
	//}
}
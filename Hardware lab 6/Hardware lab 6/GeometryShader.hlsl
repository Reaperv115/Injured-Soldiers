#pragma pack_matrix(row_major)


struct GSOutput
{
	float4 pos : SV_POSITION;
};

struct GSInput
{
    float4 coords : SV_POSITION;
};

cbuffer theMatrices : register(b2)
{
    float4x4 WorldArray[2];
    float4x4 perspectiveMat;
    float4x4 viewMat;
};

[maxvertexcount(3)]
void main(point GSInput input[1] : POSITION, inout TriangleStream< GSOutput > output)
{
    GSOutput verts[3] =
    {
        float4(1, 0, 0, 1),
        float4(0, 1, 0, 1),
        float4(0, 0, 1, 1)
    };

    verts[0].pos = input[0].coords;
    verts[0].pos.x -= 1.0f;

    verts[2].pos = verts[0].pos;
    verts[2].pos.x += 1.0f;

    verts[1].pos.xyz = input[0].coords.xyz;
    //verts[1].pos.y += 1.0f;
    //verts[2].pos.z += 1.0f;

    //verts[0].pos.xyz = input[0].coords.xyz;
    //verts[0].pos.z -= 0.5f;

    //verts[2].pos = verts[0].pos;
    //verts[2].pos.x += 1.0f;

    //verts[1].pos.xyz = input[0].coords.xyz;

    for (uint i = 0; i < 3; ++i)
    {
        verts[i].pos = mul(verts[i].pos, WorldArray[0]);
        verts[i].pos = mul(verts[i].pos, viewMat);
        verts[i].pos = mul(verts[i].pos, perspectiveMat);
    }

    output.Append(verts[0]);
    output.Append(verts[1]);
    output.Append(verts[2]);

    //output.RestartStrip();
}
#pragma pack_matrix(row_major)


struct GSOutput
{
	float4 pos : SV_POSITION;
    float4 col : COLOR;
};

struct GSInput
{
    float4 coords : SV_POSITION;
    float4 rgb : COLOR;
};

cbuffer theMatrices : register(b2)
{
    float4x4 WorldArray[2];
    float4x4 perspectiveMat;
    float4x4 viewMat;
};

[maxvertexcount(3)]
void main(triangle GSInput input[3], inout TriangleStream< GSOutput > output)
{
    GSOutput verts[3];
    //{
    //    float4(1, 0, 0, 1),
    //    float4(0, 1, 0, 1),
    //    float4(0, 0, 1, 1)
    //};


    verts[0].pos = input[0].coords;
    verts[0].col = float4(0.0f, 0.0f, 0.0f, 0.0f);

    verts[1].pos = input[1].coords;
    verts[1].pos = float4(0.0f, 0.0f, 0.0f, 0.0f);

    verts[2].pos = input[2].coords;
    verts[2].col = float4(0.0f, 0.0f, 0.0f, 0.0f);

    for (uint i = 0; i < 3; ++i)
    {
        verts[i].pos = mul(verts[i].pos, viewMat);
        verts[i].pos = mul(verts[i].pos, perspectiveMat);
    }

    verts[0].pos.x += 0.5f;
    verts[2].pos.x -= 0.5f;
    verts[1].pos.y += 1000.0f;

    //verts[0].pos = float4(-1, 0, 0, 1);
    //verts[1].pos = float4(0, 1, 0, 1);
    //verts[2].pos = float4(1, 0, 0, 1);

    

    output.Append(verts[0]);
    output.Append(verts[1]);
    output.Append(verts[2]);

    //output.RestartStrip();
}
#pragma pack_matrix(row_major)



struct INPUT_VERTEX
{
	float4 coordinate : POSITION;
};

struct OUTPUT_VERTEX
{
	float4 colorOut : COLOR;
	float4 projectedCoordinate : SV_POSITION;
    float4 normal : NORMAL;
};

cbuffer theMatrices : register(b2)
{
	float4x4 worldMat;
	float4x4 perspectiveMat;
	float4x4 viewMat;
	float4x4 projection;
    float4x4 cam;
};

cbuffer theLight : register(b1)
{
    float4 vec; //the lights' vector
    float4 color; //the lights' color
    float4 norm;
}

// TODO: PART 3 STEP 2a
cbuffer THIS_IS_VRAM : register( b0 )
{
	float4 constantColor;
	float2 constantOffset;
	float2 padding;
};

OUTPUT_VERTEX main( INPUT_VERTEX fromVertexBuffer )
{
	OUTPUT_VERTEX sendToRasterizer = (OUTPUT_VERTEX)0;
	sendToRasterizer.projectedCoordinate.w = 1;

	fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, worldMat);
	fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, viewMat);
	fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, perspectiveMat);

   


	return sendToRasterizer;
}
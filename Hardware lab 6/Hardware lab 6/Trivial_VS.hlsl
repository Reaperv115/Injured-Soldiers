#pragma pack_matrix(row_major)

struct INPUT_VERTEX
{
	float4 coordinate : POSITION;
    float4 color : RGBVal;
    float3 normal : theNormal;
    float3 dir : dir;
};

struct OUTPUT_VERTEX
{
	float4 projectedCoordinate : SV_POSITION;
	float4 colorOut : RGBVal;
    float3 normal : theNORMAL;
    float3 dir : dir;
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
    float4 lColor; //the lights' color
}

cbuffer Cube : register(b3)
{
	float4 cColor; //color of the cube
	float3 norm; //normal of a face

}

// TODO: PART 3 STEP 2a
cbuffer THIS_IS_VRAM : register( b0 )
{
	float4 constantColor;
	float2 constantOffset;
	float2 padding;
};

OUTPUT_VERTEX main( INPUT_VERTEX fromVertexBuffer)
{

	OUTPUT_VERTEX sendToRasterizer = (OUTPUT_VERTEX)0;
	sendToRasterizer.projectedCoordinate.w = 1;

	fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, worldMat);
	fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, viewMat);
	fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, perspectiveMat);



    sendToRasterizer.projectedCoordinate.x = fromVertexBuffer.coordinate.x;
    sendToRasterizer.projectedCoordinate.y = fromVertexBuffer.coordinate.y;
    sendToRasterizer.projectedCoordinate.z = fromVertexBuffer.coordinate.z;
    sendToRasterizer.projectedCoordinate.w = fromVertexBuffer.coordinate.w;
    sendToRasterizer.colorOut = fromVertexBuffer.color;
   

	return sendToRasterizer;
}
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

   

	return sendToRasterizer;
}
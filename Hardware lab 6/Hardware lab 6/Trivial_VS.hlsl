#pragma pack_matrix(row_major)

//DONT CHAGE INPUT LAYOUT, JUST TREAT COORDINATES LIKE UVs
//and dont transform the vertices, just send them to the pixel shader
struct INPUT_VERTEX
{
	float4 coordinate : POSITION;
};

struct OUTPUT_VERTEX
{
	float4 projectedCoordinate : SV_POSITION;
	float4 colorOut : RGBVal;
    float3 normal : theNORMAL;
    float3 dir : dir;
    float2 text : POSITION;
    //float3 lsPos;
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

    float4x4 thevMat = viewMat;

	//fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, worldMat);
	//fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, viewMat);
	//fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, perspectiveMat);

    thevMat = mul(thevMat, worldMat);
    fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, thevMat);


    sendToRasterizer.projectedCoordinate.x = fromVertexBuffer.coordinate.x;
    sendToRasterizer.projectedCoordinate.y = fromVertexBuffer.coordinate.y;
    sendToRasterizer.projectedCoordinate.z = fromVertexBuffer.coordinate.z;
    sendToRasterizer.projectedCoordinate.w = fromVertexBuffer.coordinate.w;

    sendToRasterizer.text.xy = fromVertexBuffer.coordinate.xy;

   

	return sendToRasterizer;
}
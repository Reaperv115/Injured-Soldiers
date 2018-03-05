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
    float3 lsPos : POSITION;
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

    //TRYING TO GRAB THE LOCAL SPACE POISITON TO SEND IT TO THE PIXEL SHADER
    sendToRasterizer.lsPos = fromVertexBuffer.coordinate;

    fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, worldMat);
    fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, viewMat);
    fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, perspectiveMat);

    //DETERMINING CAM POS IN WORLD SPACE
    thevMat = mul(viewMat, worldMat);

    //MOVING CUBE TO CAM POS IN WORLD SPACE
    //fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, worldMat);
    //fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, thevMat);
    

    //TODO: TURN CUBE INSIDE OUT
    
    
    

    //UPDATING OUTGOING VARIABLE EITH DATA
    sendToRasterizer.projectedCoordinate.x = fromVertexBuffer.coordinate.x;
    sendToRasterizer.projectedCoordinate.y = fromVertexBuffer.coordinate.y;
    sendToRasterizer.projectedCoordinate.z = fromVertexBuffer.coordinate.z;
    sendToRasterizer.projectedCoordinate.w = fromVertexBuffer.coordinate.w;

   
    //SENDING DATA TO PIXELSHADER
	return sendToRasterizer;
}
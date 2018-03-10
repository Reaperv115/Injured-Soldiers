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
    //float3 text : TEXTURE;
};

cbuffer theMatrices : register(b2)
{
	float4x4 CUBEworldMat;
    float4x4 SWATworldmat;
    float4x4 PILLARworldMat;
    float4x4 GRIDworldMat;
	float4x4 perspectiveMat;
	float4x4 viewMat;
	float4x4 projection;
    float4x4 cam;
};

OUTPUT_VERTEX main( INPUT_VERTEX fromVertexBuffer)
{
	OUTPUT_VERTEX sendToRasterizer = (OUTPUT_VERTEX)0;
	sendToRasterizer.projectedCoordinate.w = 1;



    //TRYING TO GRAB THE LOCAL SPACE POISITON TO SEND IT TO THE PIXEL SHADER
    sendToRasterizer.lsPos = fromVertexBuffer.coordinate;

    //DETERMINING CAM POS IN WORLD SPACE
    //thevMat = mul(CUBEworldMat, viewMat);

    fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, CUBEworldMat);
    fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, viewMat);
    fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, perspectiveMat);

    

    //MOVING CUBE TO CAM POS IN WORLD SPACE
    //thevMat = transpose(thevMat);
    //fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, viewMat);
    //fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, worldMat);
    //fromVertexBuffer.coordinate = mul(fromVertexBuffer.coordinate, perspectiveMat);
    
    //sendToRasterizer.text = fromVertexBuffer.coordinate;
    

    //UPDATING OUTGOING VARIABLE EITH DATA
    sendToRasterizer.projectedCoordinate.x = fromVertexBuffer.coordinate.x;
    sendToRasterizer.projectedCoordinate.y = fromVertexBuffer.coordinate.y;
    sendToRasterizer.projectedCoordinate.z = fromVertexBuffer.coordinate.z;
    sendToRasterizer.projectedCoordinate.w = fromVertexBuffer.coordinate.w;

   
    //SENDING DATA TO PIXELSHADER
	return sendToRasterizer;
}
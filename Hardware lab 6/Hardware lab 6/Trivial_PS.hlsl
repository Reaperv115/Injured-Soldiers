cbuffer theLight : register(b0)
{
	float3 vec; //vector of the light
	float4 color; //color of the light
}

cbuffer Cube : register(b1)
{
	float4 surfNorm; //normal for that surface
	float4 surfColor; //color of the surface
}


float4 main( float4 colorFromRasterizer : COLOR, float4 col : COLOR, float4 surfCol : COLOR) : SV_TARGET
{
	col = color;
	surfCol = surfColor;

	float lightRat = saturate(dot(vec.xyz * -1, normalize(surfNorm)));
	surfCol.argb = lightRat * col.argb * surfCol.argb;
	colorFromRasterizer.argb = surfCol.argb;

	return colorFromRasterizer;
}
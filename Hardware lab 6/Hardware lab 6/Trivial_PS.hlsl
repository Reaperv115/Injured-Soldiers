cbuffer theLight : register(b0)
{
	float3 vec; //vector of the light
	float4 lColor; //color of the light
}

cbuffer Cube : register(b1)
{
	float4 norm; //normal for that surface
	float4 cColor; //color of the surface
}


float4 main( float4 colorFromRasterizer : COLOR, float4 col : COLOR, float4 surfCol : COLOR) : SV_TARGET
{
	col = lColor;
	surfCol = cColor;

	float lightRat = saturate(dot(vec.xyz * -1, normalize(norm)));
	surfCol.argb = lightRat * col.argb * surfCol.argb;
	colorFromRasterizer.argb = surfCol.argb;

	return colorFromRasterizer;
}
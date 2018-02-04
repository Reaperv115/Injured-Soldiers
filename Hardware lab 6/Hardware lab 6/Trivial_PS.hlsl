float4 main( float4 colorFromRasterizer : COLOR) : SV_TARGET
{
    float lightRat = saturate(dot())

	return colorFromRasterizer;
}
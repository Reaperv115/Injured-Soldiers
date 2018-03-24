struct outPut
{
    float4 pos : SV_POSITION;
};


float4 main(outPut goout) : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}
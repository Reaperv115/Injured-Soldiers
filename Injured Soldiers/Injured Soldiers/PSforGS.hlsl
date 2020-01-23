struct PS_Out
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
};


float4 main(PS_Out outing) : SV_TARGET
{
    return outing.col;

	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}
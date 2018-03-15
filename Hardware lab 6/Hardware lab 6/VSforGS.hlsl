#pragma pack_matrix(row_major)

struct Input
{
    float3 pos : POSITION;
};

struct Output
{
    float4 pos : SV_POSITION;
};



Output main(Input comingIn)
{
    Output goingOut = (Output)0;

    //comingIn.pos = float4(comingIn.pos, 1.0f);

    goingOut.pos = float4(comingIn.pos, 1.0f);

    return goingOut;

	//return pos;
}
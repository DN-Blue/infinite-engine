
cbuffer MaterialInput:register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
	float4 viewPos;
    float4 time;
};



struct VIn{
    float3 Position:POSITION;
    float3 Normal:NORMAL;
    float2 TexCoord:TEXCOORD;
};

struct VOut{
    float4 Pos:SV_POSITION;
    float3 PosW:POSITION;
    float3 NormalW:NORMAL;
    float2 TexCoord:TEXCOORD;
};


VOut vsmain( VIn vin )
{
    VOut vout;
    vout.Pos=mul(float4(vin.Position,1),World);
    vout.Pos=mul(vout.Pos,View);
    vout.Pos=mul(vout.Pos,Projection);
    vout.PosW=vin.Position;
    vout.NormalW=vin.Position;
    vout.TexCoord=float2(0,0);
    return vout;
}

 float4 psmain( VOut pin ) : SV_Target
 {
    return float4((time.x),0,0,1);
 }
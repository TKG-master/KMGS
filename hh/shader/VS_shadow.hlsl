#include "common.hlsl"

PS_IN main(in VS_IN In)
{
    PS_IN Out;
    
    float4 Pos = float4(In.Position.xyz, 1.0f);
	
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);

    Out.Position = mul(In.Position, wvp);
    Out.TexCoord = In.TexCoord;
    Out.Diffuse = In.Diffuse * Material.Diffuse;
    
    matrix lwvp;
    lwvp = mul(World, LightView);
    lwvp = mul(lwvp, LightProjection);
   
    Out.screenPos = mul(Pos, lwvp);
	
    return Out;
}
#include "common.hlsl"

PS_IN main(in VS_IN In)
{
    PS_IN Out;
    
    // �r���[�s�񂩂畽�s�ړ��𖳌���
    matrix viewNoTranslation = View;
    viewNoTranslation._41 = 0.0f;
    viewNoTranslation._42 = 0.0f;
    viewNoTranslation._43 = 0.0f;
	
    matrix wvp;
    wvp = mul(World, viewNoTranslation);
    wvp = mul(wvp, Projection);

    Out.Position = mul(In.Position, wvp);
    Out.TexCoord = In.TexCoord;
    Out.Diffuse = In.Diffuse * Material.Diffuse;
	
    return Out;
}

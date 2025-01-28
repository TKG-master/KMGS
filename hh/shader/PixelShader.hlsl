#include "common.hlsl"


Texture2D tex : register(t0);
//�V���h�E�}�b�v
Texture2D g_ShadowTexture : register(t2);

SamplerState samp : register(s0);
//�e���s���V�F�[�_�[
float4 Shadow(PS_IN pin)
{
    float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    //���_���W�����ʏ��UV���W���擾
    float2 screenUV = pin.screenPos.xy / pin.screenPos.w;
    screenUV = screenUV * 0.5f + 0.5f;
    screenUV.y = 1.0f - screenUV.y;
    //���_���W����A�J��������̉��s���擾
    float objDepth = pin.screenPos.z / pin.screenPos.w;
    screenUV = saturate(screenUV);
    
    float texDepth = g_ShadowTexture.Sample(samp, screenUV).r;
    
    if (screenUV.x <= 0.0f || screenUV.x >= 1.0f ||
        screenUV.y <= 0.0f || screenUV.y >= 1.0f)
    {
        texDepth = 1.0f;
    }
    
    color.rbg = step(objDepth, texDepth);
    return color;
}






float4 main(PS_IN pin) : SV_TARGET
{

    float4 color = tex.Sample(samp, pin.TexCoord);
    color *= Shadow(pin);
    return color;

}

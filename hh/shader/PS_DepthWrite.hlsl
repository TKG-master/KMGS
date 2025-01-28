#include "common.hlsl"

float4 main(PS_IN pin) : SV_TARGET
{
    float depth = pin.Position.z;
	return float4(depth, 0.0f, 0.0f, 1.0f);
}
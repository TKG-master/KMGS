#include "common.hlsl"

//PS_IN main(VS_IN vin)
//{
// //   PS_IN vout;
	
// //   float4 Pos = float4(vin.Position.xyz,1.0f);
//	////vout.pos = vin.pos;
// //   vout.pos = mul(vin.Position, World);
//	//// ピクセルシェーダーに渡すために、途中で変数にコピー
// //   //vout.worldPos.x =World._m30_m33_m33_m33 ;
// //   //vout.worldPos.y =World._m31_m33_m33_m33 ;
// //   //vout.worldPos.z = World._m32_m33_m33_m33;
// //   vout.worldPos = vout.pos;
    
// //   matrix lwvp;
// //   lwvp = mul(World, LightView);
// //   lwvp = mul(lwvp, LightProjection);
   
// //   vout.ShadowPos = mul(Pos, lwvp);

    
// //   vout.pos = mul(vout.pos, View);
// //   vout.pos = mul(vout.pos, Projection);

// //   vout.screenPos = vout.pos;

// //   vout.uv = (vin.TexCoord);
// //   vout.normal = mul(vin.Normal, World);
// //   vout.Diffuse = vin.Diffuse*Material.Diffuse;
// //   return vout;
//}
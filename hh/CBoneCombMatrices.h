#pragma once
#include	<Windows.h>
#include	<directxmath.h>
#include	<d3d11.h>
#include	<wrl/client.h>
#include	"renderer.h"
#include	"NonCopyable.h"

class CBoneCombMatrices : NonCopyable
{
	CBBoneCombMatrix		m_BoneCombMatrices{};							// 行列群
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_ConstantBufferBoneMatrices{};	// 定数バッファ

public:
	CBoneCombMatrices() {}
	~CBoneCombMatrices()
	{
	}

	// 定数バッファ生成し内容を更新する
	bool Create(const CBBoneCombMatrix& bonecombmatrices);

	// 定数バッファを更新する
	void Update();

	// GPUにセット
	void SetGPU();

	// 行列群をCBに反映させる
	void SetBoneMatrices(const CBBoneCombMatrix& bonecombmatrices);
};
#pragma once

#include	"CBoneCombMatrices.h"
#include	"dx11helper.h"

// 定数バッファ生成し内容を更新する
bool CBoneCombMatrices::Create(const CBBoneCombMatrix& bonecombmatrices) {

	ID3D11Device* dev;
	dev = Renderer::GetDevice();

	// コンスタントバッファ作成
	bool sts = CreateConstantBufferWrite(
		dev,												// デバイス
		sizeof(CBBoneCombMatrix),							// サイズ
		m_ConstantBufferBoneMatrices.GetAddressOf());		// コンスタントバッファ４
	if (!sts) {
		MessageBox(NULL, "CreateBuffer(constant buffer BoneMatrices) error", "Error", MB_OK);
		return false;
	}

	// 行列群をセット
	m_BoneCombMatrices = bonecombmatrices;
	Update();

	return true;
}

// 定数バッファを更新する
void CBoneCombMatrices::Update()
{
	ID3D11DeviceContext* devcontext;
	devcontext = Renderer::GetDeviceContext();

	//定数バッファ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;

	HRESULT hr = devcontext->Map(
		m_ConstantBufferBoneMatrices.Get(),
		0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	if (SUCCEEDED(hr))
	{
		memcpy(msr.pData, &m_BoneCombMatrices, sizeof(CBBoneCombMatrix));
		Renderer::GetDeviceContext()->Unmap(m_ConstantBufferBoneMatrices.Get(), 0);
	}
}

// GPUにセット
void CBoneCombMatrices::SetGPU() {

	ID3D11DeviceContext* devcontext;
	devcontext = Renderer::GetDeviceContext();

	// コンスタントバッファをｂ５レジスタへセット（頂点シェーダー用）
	devcontext->VSSetConstantBuffers(5, 1, m_ConstantBufferBoneMatrices.GetAddressOf());
}

void CBoneCombMatrices::SetBoneMatrices(const CBBoneCombMatrix& bonecombmatrices)
{
	// 行列群をメモリにセット
	m_BoneCombMatrices = bonecombmatrices;

	// 定数バッファを更新
	Update();
}


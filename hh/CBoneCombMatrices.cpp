#pragma once

#include	"CBoneCombMatrices.h"
#include	"dx11helper.h"

// �萔�o�b�t�@���������e���X�V����
bool CBoneCombMatrices::Create(const CBBoneCombMatrix& bonecombmatrices) {

	ID3D11Device* dev;
	dev = Renderer::GetDevice();

	// �R���X�^���g�o�b�t�@�쐬
	bool sts = CreateConstantBufferWrite(
		dev,												// �f�o�C�X
		sizeof(CBBoneCombMatrix),							// �T�C�Y
		m_ConstantBufferBoneMatrices.GetAddressOf());		// �R���X�^���g�o�b�t�@�S
	if (!sts) {
		MessageBox(NULL, "CreateBuffer(constant buffer BoneMatrices) error", "Error", MB_OK);
		return false;
	}

	// �s��Q���Z�b�g
	m_BoneCombMatrices = bonecombmatrices;
	Update();

	return true;
}

// �萔�o�b�t�@���X�V����
void CBoneCombMatrices::Update()
{
	ID3D11DeviceContext* devcontext;
	devcontext = Renderer::GetDeviceContext();

	//�萔�o�b�t�@��������
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

// GPU�ɃZ�b�g
void CBoneCombMatrices::SetGPU() {

	ID3D11DeviceContext* devcontext;
	devcontext = Renderer::GetDeviceContext();

	// �R���X�^���g�o�b�t�@�����T���W�X�^�փZ�b�g�i���_�V�F�[�_�[�p�j
	devcontext->VSSetConstantBuffers(5, 1, m_ConstantBufferBoneMatrices.GetAddressOf());
}

void CBoneCombMatrices::SetBoneMatrices(const CBBoneCombMatrix& bonecombmatrices)
{
	// �s��Q���������ɃZ�b�g
	m_BoneCombMatrices = bonecombmatrices;

	// �萔�o�b�t�@���X�V
	Update();
}


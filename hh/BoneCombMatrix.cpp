#pragma once

#include	"BoneCombMatrix.h"
#include	"dx11helper.h"

// �萔�o�b�t�@���������e���X�V����
bool BoneCombMatrix::Create() {

	ID3D11Device* dev;
	dev = Renderer::GetDevice();

	// �R���X�^���g�o�b�t�@�쐬
	bool sts = CreateConstantBufferWrite(
		dev,								// �f�o�C�X
		sizeof(CBBoneCombMatrix),			// �T�C�Y
		ConstantBuffer.GetAddressOf());		// �R���X�^���g�o�b�t�@
	if (!sts) {
		MessageBox(NULL, "CreateBuffer(constant buffer BoneMatrices) error", "Error", MB_OK);
		return false;
	}

	// �s��Q��萔�o�b�t�@�փZ�b�g
	Update();

	return true;
}

// �萔�o�b�t�@���X�V����
void BoneCombMatrix::Update()
{
	ID3D11DeviceContext* devcontext;
	devcontext = Renderer::GetDeviceContext();

	//�萔�o�b�t�@��������
	D3D11_MAPPED_SUBRESOURCE msr;

	HRESULT hr = devcontext->Map(
		ConstantBuffer.Get(),
		0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	if (SUCCEEDED(hr))
	{
		memcpy(msr.pData, &ConstantBufferMemory, sizeof(CBBoneCombMatrix));
		Renderer::GetDeviceContext()->Unmap(ConstantBuffer.Get(), 0);
	}
}

// GPU�ɃZ�b�g
void BoneCombMatrix::SetGPU() {

	ID3D11DeviceContext* devcontext;
	devcontext = Renderer::GetDeviceContext();

	// �R���X�^���g�o�b�t�@�����T���W�X�^�փZ�b�g�i���_�V�F�[�_�[�p�j
	devcontext->VSSetConstantBuffers(5, 1, ConstantBuffer.GetAddressOf());
}


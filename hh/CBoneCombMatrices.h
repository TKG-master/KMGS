#pragma once
#include	<Windows.h>
#include	<directxmath.h>
#include	<d3d11.h>
#include	<wrl/client.h>
#include	"renderer.h"
#include	"NonCopyable.h"

class CBoneCombMatrices : NonCopyable
{
	CBBoneCombMatrix		m_BoneCombMatrices{};							// �s��Q
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_ConstantBufferBoneMatrices{};	// �萔�o�b�t�@

public:
	CBoneCombMatrices() {}
	~CBoneCombMatrices()
	{
	}

	// �萔�o�b�t�@���������e���X�V����
	bool Create(const CBBoneCombMatrix& bonecombmatrices);

	// �萔�o�b�t�@���X�V����
	void Update();

	// GPU�ɃZ�b�g
	void SetGPU();

	// �s��Q��CB�ɔ��f������
	void SetBoneMatrices(const CBBoneCombMatrix& bonecombmatrices);
};
#pragma once
#include	<Windows.h>
#include	<directxmath.h>
#include	<d3d11.h>
#include	<wrl/client.h>
#include	"renderer.h"
#include	"NonCopyable.h"

struct BoneCombMatrix : NonCopyable
{
	CBBoneCombMatrix	 ConstantBufferMemory{};					// �s��Q
	Microsoft::WRL::ComPtr<ID3D11Buffer> ConstantBuffer{};			// �萔�o�b�t�@

	BoneCombMatrix() {}
	~BoneCombMatrix()
	{
	}

	// �萔�o�b�t�@���������e���X�V����
	bool Create();

	// �萔�o�b�t�@���X�V����
	void Update();

	// GPU�ɃZ�b�g
	void SetGPU();
};


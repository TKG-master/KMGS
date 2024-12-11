#pragma once
#include	<simplemath.h>
#include	"BoneCombMatrix.h"
#include	"CAnimationMesh.h"

class AnimObj
{
	// SRT���
	DirectX::SimpleMath::Vector3 m_Position = { 0,0,0 };
	DirectX::SimpleMath::Vector3 m_Rotation = { 0,0,0 };
	DirectX::SimpleMath::Vector3 m_Scale = { 0.1f,0.1f,0.1f };

	// �{�[���R���r�l�[�V�����s��p�萔�o�b�t�@���e
	BoneCombMatrix m_BoneCombMatrix{};							// 20240723

	// �A�j���[�V�������b�V��
	CAnimationMesh* m_AnimMesh = nullptr;

	// ���݂̃A�j���[�V����
	aiAnimation* m_CurrentAnimation = nullptr;
	aiAnimation* m_FromAnimation = nullptr;
	aiAnimation* m_ToAnimation = nullptr;

	// ���݃t���[��
	float m_CurrentFrame = 0;
	// �u�����h���C�g
	float m_BlendRate = 0.0f;									// ���[�V�����̃u�����h��

public:
	void Init();
	void Update(float dt);

	void BlendUpdate(float dt);

	void Draw(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 Scal , DirectX::SimpleMath::Vector3 Roatat);
	void SetAnimationMesh(CAnimationMesh* animmesh) { m_AnimMesh = animmesh; }
	void SetPosition(DirectX::SimpleMath::Vector3 pos) { m_Position = pos; }
	void SetScale(DirectX::SimpleMath::Vector3 scale) { m_Scale = scale; }
	void SetRotation(DirectX::SimpleMath::Vector3 rotation) { m_Rotation = rotation; }

	void SetCurrentAnimation(aiAnimation* anim) { m_CurrentAnimation = anim; }

	void SetFromAnimation(aiAnimation* anim) { m_FromAnimation = anim; }

	void SetToAnimation(aiAnimation* anim) { m_ToAnimation = anim; }

	void SetBlendRate(float rate) { m_BlendRate = rate; }


};


#include "AnimObj.h"

using namespace DirectX::SimpleMath;

void AnimObj::Init()
{
	// �{�[���R���r�l�[�V�����s�񏉊���
	m_BoneCombMatrix.Create();							// 20240723 

}

void AnimObj::Update(float dt)
{
	int frame = static_cast<int>(m_CurrentFrame);

	// �A�j���[�V�������b�V���̃J�����g�A�j���[�V�������Z�b�g
	m_AnimMesh->SetCurentAnimation(m_CurrentAnimation);

	// �A�j���[�V�������b�V���X�V
	m_AnimMesh->Update(m_BoneCombMatrix, frame);

	// �t���[���X�V	
	m_CurrentFrame += dt;

}

void AnimObj::BlendUpdate(float dt)
{
	int frame = static_cast<int>(m_CurrentFrame);

	// �A�j���[�V�������b�V���̃u�����h�A�j���[�V�������Z�b�g
	m_AnimMesh->SetFromAnimation(m_FromAnimation);
	m_AnimMesh->SetToAnimation(m_ToAnimation);

	m_AnimMesh->BlendUpdate(m_BoneCombMatrix, frame, frame, m_BlendRate);

	// �t���[���X�V	
	m_CurrentFrame += dt;
}

void AnimObj::Draw(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 Scal , DirectX::SimpleMath::Vector3 Roatat)
{
	Matrix rmtx = Matrix::CreateFromYawPitchRoll(Roatat.y, Roatat.x, Roatat.z);
	Matrix smtx = Matrix::CreateScale(Scal.x, Scal.y, Scal.z);
	Matrix tmtx = Matrix::CreateTranslation(pos.x, pos.y, pos.z);

	Matrix wmtx = smtx * rmtx * tmtx;

	Renderer::SetWorldMatrix(&wmtx);

	// �{�[���R���r�l�[�V�����s��p�萔�o�b�t�@�X�V
	m_BoneCombMatrix.Update();

	// �萔�o�b�t�@GPU�փZ�b�g
	m_BoneCombMatrix.SetGPU();

	// ���b�V���`��
	m_AnimMesh->Draw();
}

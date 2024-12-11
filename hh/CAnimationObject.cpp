#include "CAnimationObject.h"

using namespace DirectX::SimpleMath;

void CAnimationObject::Init()
{
	// �{�[���R���r�l�[�V�����s�񏉊���
	m_BoneCombMatrix.Create();							// 20240723 
}

void CAnimationObject::Update(float dt)
{
	int frame = static_cast<int>(m_CurrentFrame);

	// �A�j���[�V�������b�V���̃J�����g�A�j���[�V�������Z�b�g
	m_AnimMesh->SetCurentAnimation(m_CurrentAnimation);

	// �A�j���[�V�������b�V���X�V
	m_AnimMesh->Update(m_BoneCombMatrix, frame);

	// �t���[���X�V	
	m_CurrentFrame += dt;
}

void CAnimationObject::BlendUpdate(float dt)
{
	int frame = static_cast<int>(m_CurrentFrame);

	// �A�j���[�V�������b�V���̃u�����h�A�j���[�V�������Z�b�g
	m_AnimMesh->SetFromAnimation(m_FromAnimation);
	m_AnimMesh->SetToAnimation(m_ToAnimation);

	m_AnimMesh->BlendUpdate(m_BoneCombMatrix, frame, frame, m_BlendRate);

	// �t���[���X�V	
	m_CurrentFrame += dt;
}

void CAnimationObject::Draw()
{
	Matrix rmtx = Matrix::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(m_Rotation.y), // Yaw (�x�� �� ���W�A��)
		DirectX::XMConvertToRadians(m_Rotation.x), // Pitch (�x�� �� ���W�A��)
		DirectX::XMConvertToRadians(m_Rotation.z)  // Roll (�x�� �� ���W�A��)
	);
	Matrix smtx = Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);
	Matrix tmtx = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);

	Matrix wmtx = smtx * rmtx * tmtx;

	Renderer::SetWorldMatrix(&wmtx);

	// �{�[���R���r�l�[�V�����s��p�萔�o�b�t�@�X�V
	m_BoneCombMatrix.Update();

	// �萔�o�b�t�@GPU�փZ�b�g
	m_BoneCombMatrix.SetGPU();

	// ���b�V���`��
	m_AnimMesh->Draw();
}

void CAnimationObject::ModifyRotation()
{
	if (m_Rotation.x < 0)
	{
		m_Rotation.x = 359;
	}
	if (m_Rotation.y < 0)
	{
		m_Rotation.y = 359;
	}
	if (m_Rotation.z < 0)
	{
		m_Rotation.z = 359;
	}

	if (m_Rotation.x >= 360)
	{
		m_Rotation.x = 0;
	}
	if (m_Rotation.y >= 360)
	{
		m_Rotation.y = 0;
	}
	if (m_Rotation.z >= 360)
	{
		m_Rotation.z = 0;
	}
}
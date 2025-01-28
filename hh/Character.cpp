#include "Character.h"

bool Character::AnimationBrend()
{
	//From�擾
	aiAnimation* fromanimation = m_AnimationData[m_FromAnimationName].GetAnimation(m_FromAnimationName);
	m_AnimationObject.SetFromAnimation(fromanimation);

	//To�擾
	aiAnimation* toanimation = m_AnimationData[m_ToAnimationName].GetAnimation(m_ToAnimationName);
	m_AnimationObject.SetToAnimation(toanimation);

	//from��to����v�A�u�����h�����Ȃ��ꍇ�����ŏI��������
	if (fromanimation == toanimation) { return false; }

	// �u�����h���[�g�ݒ�
	m_BlendRate += m_AnimationBrendSpeed;
	if (m_BlendRate >= 1.0f)
	{
		//�u�����h���S�ɏI����
		m_BlendRate = 1.0f;
		m_AnimationObject.SetBlendRate(m_BlendRate);
		//�ς��؂����̂�From��To�������
		m_FromAnimationName = m_ToAnimationName;
		m_BlendRate = 0.0f;
		this->AnimEndState = true;
		return true;
	}
	m_AnimationObject.SetBlendRate(m_BlendRate);
	this->AnimEndState = false;
	return false;
}

void Character::Init(
	std::string ModelName, std::string TexFolderPath,
	std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader)
{
	DepthS.Create("shader/vertexLightingOneSkinVS.hlsl","shader/PS_DepthWrite.hlsl");


	STATUS = IDLE;

	// �A�j���[�V�������b�V���ǂݍ���
	m_AnimationMesh.Load(ModelName, TexFolderPath);

	// �I�u�W�F�N�g�Ƀ��b�V�����Z�b�g
	m_AnimationObject.SetAnimationMesh(&m_AnimationMesh);

	// �V�F�[�_�I�u�W�F�N�g����
	m_Shader.Create(vShader, pShader);

	// �A�j���[�V�����f�[�^�ǂݍ���
	for (int i = 0; i < MotionName.size(); i++)
	{
		m_AnimationData[MotionName[i].MotionKey].LoadAnimation
		(MotionName[i].MotionFile, MotionName[i].MotionKey);
	}

	// �A�j���[�V�����f�[�^�擾
	const std::string s = MotionName[0].MotionKey;
	aiAnimation* animation = m_AnimationData[s].GetAnimation(s);
	// ���݂̃A�j���[�V�������Z�b�g
	m_AnimationObject.SetCurrentAnimation(animation);

	// ������
	m_AnimationObject.Init();

	// �ʒu�ݒ�
	m_AnimationObject.SetPosition(DirectX::SimpleMath::Vector3(0, 0, 0));

	// �X�P�[���ݒ�
	m_AnimationObject.SetScale(DirectX::SimpleMath::Vector3(0.08f, 0.08f, 0.08f));

	// �ŏ��̃��[�V�����L�[�ۑ�
	m_FromAnimationName = MotionName[0].MotionKey;
	m_ToAnimationName = MotionName[0].MotionKey;


}

void Character::EnemyInit(CAnimationMesh m_AnimationMesh, std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader)
{
	STATUS = IDLE;

	// �I�u�W�F�N�g�Ƀ��b�V�����Z�b�g
	m_AnimationObject.SetAnimationMesh(&m_AnimationMesh);

	// �V�F�[�_�I�u�W�F�N�g����
	m_Shader.Create(vShader, pShader);

	// �A�j���[�V�����f�[�^�ǂݍ���
	for (int i = 0; i < MotionName.size(); i++)
	{
		m_AnimationData[MotionName[i].MotionKey].LoadAnimation
		(MotionName[i].MotionFile, MotionName[i].MotionKey);
	}

	// �A�j���[�V�����f�[�^�擾
	const std::string s = MotionName[0].MotionKey;
	aiAnimation* animation = m_AnimationData[s].GetAnimation(s);
	// ���݂̃A�j���[�V�������Z�b�g
	m_AnimationObject.SetCurrentAnimation(animation);

	// ������
	m_AnimationObject.Init();

	// �ʒu�ݒ�
	m_AnimationObject.SetPosition(DirectX::SimpleMath::Vector3(0, 0, 0));

	// �X�P�[���ݒ�
	m_AnimationObject.SetScale(DirectX::SimpleMath::Vector3(0.08f, 0.08f, 0.08f));

	// �ŏ��̃��[�V�����L�[�ۑ�
	m_FromAnimationName = MotionName[0].MotionKey;
	m_ToAnimationName = MotionName[0].MotionKey;
}

void Character::UnInit()
{

}

void Character::Update()
{
	// �A�j���[�V�����u�����h�X�V
	AnimationBrend();
	// �A�j���[�V�����I�u�W�F�N�g�X�V
	m_AnimationObject.BlendUpdate(m_AnimationSpeed);

	this->square.centerX = this->m_AnimationObject.m_Position.x;
	this->square.centerY = this->m_AnimationObject.m_Position.y;
	this->square.centerZ = this->m_AnimationObject.m_Position.z;

}

void Character::Draw()
{
	m_Shader.SetGPU();
	m_AnimationObject.Draw();


}

void Character::ModifyRotation()
{
	if (m_AnimationObject.m_Rotation.x < 0)
	{
		m_AnimationObject.m_Rotation.x = 359;
	}
	if (m_AnimationObject.m_Rotation.y < 0)
	{
		m_AnimationObject.m_Rotation.y = 359;
	}
	if (m_AnimationObject.m_Rotation.z < 0)
	{
		m_AnimationObject.m_Rotation.z = 359;
	}

	if (m_AnimationObject.m_Rotation.x >= 360)
	{
		m_AnimationObject.m_Rotation.x = 0;
	}
	if (m_AnimationObject.m_Rotation.y >= 360)
	{
		m_AnimationObject.m_Rotation.y = 0;
	}
	if (m_AnimationObject.m_Rotation.z >= 360)
	{
		m_AnimationObject.m_Rotation.z = 0;
	}
}

void Character::CollisionInit(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 size)
{
	//�����̂̒��S�_
	this->square.centerX = pos.x;
	this->square.centerY = pos.y;
	this->square.centerZ = pos.z;
	//�����̂̃T�C�Y
	this->square.sizeX = size.x;
	this->square.sizeY = size.y;
	this->square.sizeZ = size.z;
}

void Character::ShadowDraw()
{
	DepthS.SetGPU();
	m_AnimationObject.Draw();
}

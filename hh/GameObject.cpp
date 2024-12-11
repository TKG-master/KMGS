#include	"GameObject.h"
#include	<SimpleMath.h>
#include	<memory>
#include	"CShader.h"
#include	"CAnimationData.h"
#include	"CAnimationMesh.h"

using namespace DirectX::SimpleMath;

// �V�F�[�_�[
static CShader	g_Shader;

// �A�j���[�V�����f�[�^
static CAnimationData g_AnimationData[2];

// �A�j���[�V�������b�V��
static CAnimationMesh g_AnimationMesh{};

// �A�j���[�V�����I�u�W�F�N�g
AnimObj g_AnimationObject[1];


GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::Init()
{
	//�A�j���[�V�����̏�����
	this->AnimInit();
}

void GameObject::Update()
{
	//�A�j���[�V�����̃A�b�v�f�[�g
	this->AnimUpdate();
}

void GameObject::Draw()
{
	//�A�j���[�V�����̕`��
	this->AnimDraw();
}

void GameObject::Uninit()
{

}

void GameObject::AnimInit()
{
	std::vector<std::string> filename =
	{
		"assets/model/akai.fbx",
	};

	std::string texdirectory =
	{
		"assets/model",				// �e�N�X�`������i�����j			OK
	};

	std::vector<std::string> motionfile =
	{
		"assets/model/Akai_Idle.fbx",
		"assets/model/Akai_Run.fbx",
	};

	// ���f���ǂݍ���
	std::string f = filename[0];

	// �A�j���[�V�������b�V���ǂݍ���
	g_AnimationMesh.Load(f, texdirectory);


	// �I�u�W�F�N�g�Ƀ��b�V�����Z�b�g
	for (auto& obj : g_AnimationObject)
	{
		obj.SetAnimationMesh(&g_AnimationMesh);
	}

	// �V�F�[�_�I�u�W�F�N�g����
	g_Shader.Create("shader/vertexLightingOneSkinVS.hlsl", "shader/vertexLightingPS.hlsl");

	// �A�j���[�V�����f�[�^�ǂݍ���

	g_AnimationData[0].LoadAnimation(motionfile[0], "Idle");
	g_AnimationData[1].LoadAnimation(motionfile[1], "Run");

	// �A�j���[�V�����f�[�^�擾
	aiAnimation* animation1 = g_AnimationData[0].GetAnimation("Idle");
	aiAnimation* animation2 = g_AnimationData[1].GetAnimation("Run");

	// ���݂̃A�j���[�V�������Z�b�g
	g_AnimationObject[0].SetCurrentAnimation(animation1);

	// ������
	g_AnimationObject[0].Init();

	// �ʒu�ݒ�
	g_AnimationObject[0].SetPosition(this->m_Position);

	// �X�P�[���ݒ�
	g_AnimationObject[0].SetScale(this->m_Scale);
}

void GameObject::AnimUpdate()
{
	aiAnimation* fromanimation = g_AnimationData[0].GetAnimation("Idle");

	g_AnimationObject[0].SetFromAnimation(fromanimation);

	aiAnimation* toanimation = g_AnimationData[1].GetAnimation("Run");

	g_AnimationObject[0].SetToAnimation(toanimation);

	// �u�����h���[�g�ݒ�
	g_AnimationObject[0].SetBlendRate(this->BlendRate);

	// �A�j���[�V�����I�u�W�F�N�g�X�V
	g_AnimationObject[0].BlendUpdate(1.0f);					// �����œn���Ă���͍̂X�V����

}

void GameObject::AnimDraw()
{
	g_Shader.SetGPU();

	for (auto& obj : g_AnimationObject) {
		obj.Draw(this->m_Position, this->m_Scale, this->m_Rotation);
	}

}

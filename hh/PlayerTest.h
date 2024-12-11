#pragma once
#include "CBoxMesh.h"
#include "Camera.h"
#include "Input.h"


//�J���̂��߂̎���������N���X
class PlayerTest
{
private:
	//SRT���i�p�����j
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);



	//�`��̂��߂̏��i���b�V���ɂ��������j
	CIndexBuffer				m_IndexBuffer;
	CVertexBuffer<VERTEX_3D>	m_VertexBuffer;

	//�`��ׂ̈̏��i�����ڂɂ�����镔���j
	CShader		m_Shader;
	CMaterial	m_Material;
	CTexture	m_Texture;

	//�����Ă������
	DirectX::XMFLOAT3 forward = { 0,0,1 };
	//�ړ��X�s�[�h�����ϐ�
	float movespeed = 1.0f;



public:
	//�R���X�g���N�^
	PlayerTest();
	//�f�X�X�g���N�^
	~PlayerTest();

	//�v���C���[�̍X�V
	void Update();
	//������
	void Init();
	//�`��
	void Draw();
	//�v���C���[�̈ړ����x���Z�b�g
	void SetSpeed(float ac) { movespeed = ac; };
	//�v���C���[�̑��x���Q�b�g
	float GetSpeed();
	float Move(float a);
	//�����Ă�������Q�b�g
	DirectX::XMFLOAT3 GetForward();
	//�v���C���[��S�ER�ET���Q�b�g�ł���֐�
	DirectX::SimpleMath::Vector3 GetPosition();
	DirectX::SimpleMath::Vector3 GetRoatation();
	DirectX::SimpleMath::Vector3 GetScale();

	//�v���C���[��S R T���Z�b�g����֐�
	void SetPosition(DirectX::SimpleMath::Vector3 pos);
	void SetRoatation(DirectX::SimpleMath::Vector3 roa);
	void SetScale(DirectX::SimpleMath::Vector3 sca);

	

};





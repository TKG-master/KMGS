#pragma once
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CMaterial.h"
#include "CTexture.h"


class Enemy;

class Radar
{
private:
	DirectX::SimpleMath::Vector2 m_RadarCenter; // ���[�_�[�̒��S�ʒu
	std::vector<DirectX::SimpleMath::Vector2> m_EnemyPositions; // �����̓G�̈ʒu
	DirectX::SimpleMath::Vector2 relativePos;
	DirectX::SimpleMath::Vector3 playerpos;
	std::vector<int> m_EnemyIndices;

	//���[�_�[��̍��W�ւ̕ϊ������l��ێ�����
	float differenceX = 0.0f;
	float differenceY = 0.0f;

	//���[�_�[��̓G�̈ʒu��X��Y
	float SaveANSX = 0.0f;
	float SaveANSY = 0.0f;

	// �����`�̃��[�_�[�͈͓��ɓG�����邩���`�F�b�N
	float halfWidth = 100.0f; // ���[�_�[�̔���
	float halfHeight = 100.0f; // ���[�_�[�̔���

	//���[�_�[�̌��_����G�̈ʒu�̓_�̍���
	float Savedistance = 0.0f;

	// �ǉ�: �X�L�������C���̊p�x��ێ����郁���o�ϐ�
	float m_ScanLineAngle = 0.0f;

	// 1�t���[�����Ƃɉ�]����p�x�i�x�P�ʁj
	float m_ScanLineSpeed = 0.0001f; 

	CIndexBuffer				m_IndexBuffer;
	CVertexBuffer<VERTEX_3D>	m_VertexBuffer;
	CShader						m_Shader;
	CMaterial					m_Material;
	CTexture					m_Texture;

public:
	//������
	void Init();
	//�G�̈ʒu�Ǝ����̈ʒu�̍�����2D�̈ʒu�ɕϊ�
	void Update(DirectX::SimpleMath::Vector3 playerPosition, std::vector<Enemy*> enemies);
	//�`��
	void Draw(const std::vector<Enemy*>& enemies);

	void Dispose();


	DirectX::SimpleMath::Vector2 GetRadarCenter() { return m_RadarCenter; };
	DirectX::SimpleMath::Vector2 GetrelativePos() { return relativePos; };

	float SaveANSx() { return SaveANSX; };
	float SaveANSy() { return SaveANSY; };

};


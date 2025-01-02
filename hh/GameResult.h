#pragma once
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CMaterial.h"
#include "CTexture.h"

class Camera;


class GameUI
{
protected:
	DirectX::SimpleMath::Vector2 relativePos;

	DirectX::SimpleMath::Vector2 Center = DirectX::SimpleMath::Vector2(650.0f,450.0f);

	DirectX::SimpleMath::Vector2 m_RadarCenter; //���S�ʒu

	DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);

	float differenceX = 0.0f;
	float differenceY = 0.0f;

	DirectX::SimpleMath::Vector2 WH;

	float halfWidth = 700.0f;
	float halfHeight = 700.0f;

	CIndexBuffer				m_IndexBuffer;
	CVertexBuffer<VERTEX_3D>	m_VertexBuffer;
	CShader						m_Shader;
	CMaterial					m_Material;
	CTexture					m_Texture;

public:

	GameUI();
	~GameUI();

	//������
	void Init(std::string TexPaht);

	//�A�b�v�f�[�g
	void Update();

	//�`��
	void Draw();

	float GetWidth() { return this->halfWidth; };
	void SetWidth(float Width) { this->halfWidth = Width; };

	float GetHeight() { return this->halfHeight; };
	void SetHeight(float Height) { this->halfHeight = Height; };

	DirectX::SimpleMath::Vector2 GetCenter() { return this->Center; };
	void SetCenter(DirectX::SimpleMath::Vector2 center) { this->Center = center; };

	void SetColor(DirectX::SimpleMath::Color c) { this->color = c; };

	void SetFadePos(DirectX::SimpleMath::Vector3 Fadepos);

	DirectX::SimpleMath::Vector3 GetFadePos();

	// �V�����ǉ��F�X�N���[����ɕ`�悷��3D�ʒu��ݒ�
	void SetPosition(DirectX::SimpleMath::Vector3 position);

	void SetWH(DirectX::SimpleMath::Vector3 wh);
	DirectX::SimpleMath::Vector3 GetWH();
};


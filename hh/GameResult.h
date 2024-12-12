#pragma once
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CMaterial.h"
#include "CTexture.h"



class GameUI
{
private:
	DirectX::SimpleMath::Vector2 relativePos;

	DirectX::SimpleMath::Vector2 Center = DirectX::SimpleMath::Vector2(600.0f,450.0f);

	DirectX::SimpleMath::Vector2 m_RadarCenter; //���S�ʒu

	float differenceX = 0.0f;
	float differenceY = 0.0f;

	float halfWidth = 700.0f;
	float halfHeight = 700.0f;

	CIndexBuffer				m_IndexBuffer;
	CVertexBuffer<VERTEX_3D>	m_VertexBuffer;
	CShader						m_Shader;
	CMaterial					m_Material;
	CTexture					m_Texture;

public:

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


};


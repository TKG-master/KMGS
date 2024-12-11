#pragma once

#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CMaterial.h"
#include "CTexture.h"

class Field
{
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
public:
	void Init();
	void Draw();
	void Dispose();

};


#pragma once

#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CMaterial.h"
#include "CTexture.h"

class Field
{
	//SRT情報（姿勢情報）
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
	//描画のための情報（メッシュにかかわる情報）
	CIndexBuffer				m_IndexBuffer;
	CVertexBuffer<VERTEX_3D>	m_VertexBuffer;

	//描画の為の情報（見た目にかかわる部分）
	CShader		m_Shader;
	CMaterial	m_Material;
	CTexture	m_Texture;
public:
	void Init();
	void Draw();
	void Dispose();

};


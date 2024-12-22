#pragma once

#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CMaterial.h"
#include "CTexture.h"
#include "Timer.h"

class Polygon2D {
	CIndexBuffer				m_IndexBuffer;
	CVertexBuffer<VERTEX_3D>	m_VertexBuffer;
	CShader						m_Shader;
	CMaterial					m_Material;
	CTexture					m_Texture;

	// タイマーのテキストを保持
	std::string m_TimerText;


public:


	void Init(std::string TexPath);
	void Update(std::string timerText);
	void Draw();
	void Dispose();
};
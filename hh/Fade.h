#pragma once
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CMaterial.h"
#include "CTexture.h"


class Fade 
{
private:
	CIndexBuffer				m_IndexBuffer;
	CVertexBuffer<VERTEX_3D>	m_VertexBuffer;
	CShader						m_Shader;
	CMaterial					m_Material;
	CTexture					m_Texture;

	float m_Opacity;          // ���݂̕s�����x
	bool m_FadingIn;         // �t�F�[�h�C�����t�F�[�h�A�E�g��
	bool m_IsFading;         // �t�F�[�h�����ǂ���
public:
	Fade() : m_Opacity(0.0f), m_FadingIn(false), m_IsFading(false) {}

	void Init();

	void Uninit();

	void Draw();

	void FadeIn();

	void FadeOut();

	void Update();



};


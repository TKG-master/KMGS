#pragma once
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CMaterial.h"
#include "CTexture.h"



class GameUI
{
protected:
	DirectX::SimpleMath::Vector2 relativePos;

	DirectX::SimpleMath::Vector2 Center = DirectX::SimpleMath::Vector2(650.0f,450.0f);

	DirectX::SimpleMath::Vector2 m_RadarCenter; //中心位置

	DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);

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

	//初期化
	void Init(std::string TexPaht);

	//アップデート
	virtual void Update();

	//描画
	virtual void Draw();

	float GetWidth() { return this->halfWidth; };
	void SetWidth(float Width) { this->halfWidth = Width; };

	float GetHeight() { return this->halfHeight; };
	void SetHeight(float Height) { this->halfHeight = Height; };

	DirectX::SimpleMath::Vector2 GetCenter() { return this->Center; };
	void SetCenter(DirectX::SimpleMath::Vector2 center) { this->Center = center; };

	void SetColor(DirectX::SimpleMath::Color c) { this->color = c; };

	void SetFadePos(DirectX::SimpleMath::Vector3 Fadepos);

	DirectX::SimpleMath::Vector3 GetFadePos();

};


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

	DirectX::SimpleMath::Vector2 Center = DirectX::SimpleMath::Vector2(650.0f,450.0f);

	DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 0.8f);

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

	std::string id; // 識別子
	bool isVisible; // 表示状態

public:

	GameUI();
	~GameUI();

	//初期化
	void Init(std::string TexPaht);

	//アップデート
	void Update();

	//描画
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

	// 新しく追加：スクリーン上に描画する3D位置を設定
	void SetPosition(DirectX::SimpleMath::Vector3 position);

	void SetWH(DirectX::SimpleMath::Vector3 wh);
	DirectX::SimpleMath::Vector3 GetWH();

	void SetID(const std::string& id) { this->id = id; }
	const std::string& GetID() const { return id; }

	void SetVisible(bool visible) { isVisible = visible; }
	bool IsVisible() const { return isVisible; }
};


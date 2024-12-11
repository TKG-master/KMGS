#pragma once
#include	"CMesh.h"

class BoxMesh : public CMesh {
	// 法線ベクトルを計算
	// 頂点座標をノーマライズ
	void Normalize(
		DirectX::SimpleMath::Vector3 vec,
		DirectX::SimpleMath::Vector3& Normal);

	// 頂点データ生成
	void CreateVertex();
	// インデックス生成
	void CreateIndex();

public:

	void DrawInit(float x,float y,float z , std::string TexPath);

	void Init(float width, float height, float depth,
		DirectX::SimpleMath::Color color, std::string TexPath, std::string vShader = {}, std::string pShader = {}, MATERIAL mtrl = {});

	void Update();
	void Draw();

private:
	DirectX::SimpleMath::Color m_color;
	float m_lengthx = 0.0f;
	float m_lengthy = 0.0f;
	float m_lengthz = 0.0f;
};
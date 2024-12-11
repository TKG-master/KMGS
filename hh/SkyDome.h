#pragma once
#include	"CMesh.h"

class SkyDome : public CMesh
{
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
    void DrawInit(float radius, std::string TexPath);

    void Init(float radius,
        DirectX::SimpleMath::Color color, std::string TexPath, std::string vShader = {}, std::string pShader = {}, MATERIAL mtrl = {});

    void Update();
    void Draw();

private:
    DirectX::SimpleMath::Color m_color;
    float m_radius = 0.0f;
};


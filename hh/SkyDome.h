#pragma once
#include	"CMesh.h"

class SkyDome : public CMesh
{
    // �@���x�N�g�����v�Z
  // ���_���W���m�[�}���C�Y
    void Normalize(
        DirectX::SimpleMath::Vector3 vec,
        DirectX::SimpleMath::Vector3& Normal);

    // ���_�f�[�^����
    void CreateVertex();
    // �C���f�b�N�X����
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


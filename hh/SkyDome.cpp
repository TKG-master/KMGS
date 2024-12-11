#include "SkyDome.h"
using namespace DirectX::SimpleMath;

struct FACE {
    unsigned int idx[3];
};

void SkyDome::Normalize(DirectX::SimpleMath::Vector3 vec, DirectX::SimpleMath::Vector3 & Normal)
{
    vec.Normalize();
    Normal = vec;
}

void SkyDome::CreateVertex()
{
    const int latitudeBands = 30;
    const int longitudeBands = 30;

    // 頂点クリア
    m_vertices.clear();

    for (int latNumber = 0; latNumber <= latitudeBands; ++latNumber) {
        float theta = latNumber * DirectX::XM_PI / latitudeBands;
        float sinTheta = sinf(theta);
        float cosTheta = cosf(theta);

        for (int longNumber = 0; longNumber <= longitudeBands; ++longNumber) {
            float phi = longNumber * 2 * DirectX::XM_PI / longitudeBands;
            float sinPhi = sinf(phi);
            float cosPhi = cosf(phi);

            Vector3 position(
                m_radius * cosPhi * sinTheta,
                m_radius * cosTheta,
                m_radius * sinPhi * sinTheta
            );

            Vector3 normal;
            Normalize(position, normal);

            float u = 1.0f - (float(longNumber) / longitudeBands);
            float v = 1.0f - (float(latNumber) / latitudeBands);

            VERTEX_3D vertex;
            vertex.Position = position;
            vertex.Normal = normal;
            vertex.TexCoord = { u, v };
            vertex.Diffuse = m_color;

            m_vertices.emplace_back(vertex);
        }
    }
}

void SkyDome::CreateIndex()
{
    const int latitudeBands = 30;
    const int longitudeBands = 30;

    // インデックスデータクリア
    m_indices.clear();

    for (int latNumber = 0; latNumber < latitudeBands; ++latNumber) {
        for (int longNumber = 0; longNumber < longitudeBands; ++longNumber) {
            int first = (latNumber * (longitudeBands + 1)) + longNumber;
            int second = first + longitudeBands + 1;

            m_indices.emplace_back(first);
            m_indices.emplace_back(second);
            m_indices.emplace_back(first + 1);

            m_indices.emplace_back(second);
            m_indices.emplace_back(second + 1);
            m_indices.emplace_back(first + 1);
        }
    }
}

void SkyDome::DrawInit(float radius, std::string TexPath)
{
    // マテリアル生成
    MATERIAL mtrl;
    mtrl.Ambient = DirectX::SimpleMath::Color(0, 0, 0, 0);
    mtrl.Diffuse = DirectX::SimpleMath::Color(1, 1, 1, 1);
    mtrl.Emission = DirectX::SimpleMath::Color(0, 0, 0, 0);
    mtrl.Specular = DirectX::SimpleMath::Color(0, 0, 0, 0);
    mtrl.Shiness = 0;
    mtrl.TextureEnable = TRUE;

    this->Init(radius, DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f),
        TexPath, "shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl", mtrl);
}

void SkyDome::Init(float radius, DirectX::SimpleMath::Color color, std::string TexPath, std::string vShader, std::string pShader, MATERIAL mtrl)
{
    // 半径を保存
    m_radius = radius;

    // カラー値を保存
    m_color = color;

    // インデックスデータを作成
    CreateIndex();

    // 頂点データを作成
    CreateVertex();

    // マテリアル生成
    m_Material.Create(mtrl);

    // シェーダオブジェクト生成
    m_Shader.Create(vShader, pShader);

    if (TexPath != "NULL") {
        m_Texture.Load(TexPath);
    }

    CMesh::Init();
}

void SkyDome::Update()
{
    CMesh::Update();
}

void SkyDome::Draw()
{
    CMesh::Draw();
}

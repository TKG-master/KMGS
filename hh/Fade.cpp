#include "Fade.h"

using namespace DirectX::SimpleMath;

void Fade::Init()
{
    // 頂点データの準備（四角形）
    std::vector<VERTEX_3D> vertices(4);

    // 頂点の位置
    vertices[0].Position = Vector3(5000.0f, 0.0f, 0.0f);  // 左下
    vertices[1].Position = Vector3(5000.0f, 0.0f, 0.0f);  // 右下
    vertices[2].Position = Vector3(5000.0f, 6000.0f, 0.0f);  // 左上
    vertices[3].Position = Vector3(5000.0f, 6000.0f, 0.0f);  // 右上

    // 頂点の色（初期は完全に透明）
    for (int i = 0; i < 4; i++) {
        vertices[i].Diffuse = Color(1, 1, 1, 0);  // 透明
    }

    // 頂点のテクスチャ座標
    vertices[0].TexCoord = Vector2(0, 0);
    vertices[1].TexCoord = Vector2(1, 0);
    vertices[2].TexCoord = Vector2(0, 1);
    vertices[3].TexCoord = Vector2(1, 1);

    // 頂点バッファの生成
    m_VertexBuffer.Create(vertices);

    // インデックスデータ
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };
    m_IndexBuffer.Create(indices);

    // シェーダーの読み込み
    m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");

    // マテリアルの設定（透明度を管理）
    MATERIAL mtrl;
    mtrl.Ambient = Color(0, 0, 0, 0);
    mtrl.Diffuse = Color(1, 1, 1, 0);
    mtrl.Emission = Color(0, 0, 0, 0);
    mtrl.Specular = Color(0, 0, 0, 0);
    mtrl.Shiness = 0;
    mtrl.TextureEnable = TRUE;
    m_Material.Create(mtrl);

    // テクスチャの読み込み
    bool sts = m_Texture.Load("assets\\kuro.png");
    assert(sts == true);

}

void Fade::Uninit()
{

}

void Fade::Draw()
{
	// 2D描画用
	Renderer::SetWorldViewProjection2D();

	ID3D11DeviceContext* devicecontext;

	devicecontext = Renderer::GetDeviceContext();

	// トポロジーをセット（旧プリミティブタイプ）
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();
	m_Material.SetGPU();
	m_Texture.SetGPU();

	devicecontext->DrawIndexed(
		4,							// 描画するインデックス数（四角形なんで４）
		0,							// 最初のインデックスバッファの位置
		0);
}

void Fade::FadeIn()
{
    m_FadingIn = true;
    m_IsFading = true;
}

void Fade::FadeOut()
{
    m_FadingIn = false;
    m_IsFading = true;
}

void Fade::Update()
{
    if (m_IsFading) {
        // フェードインかフェードアウトかの判定
        if (m_FadingIn) {
            m_Opacity += 0.05f;  // 速さを調整（0.05はフェードインのスピード）
            if (m_Opacity >= 1.0f) {
                m_Opacity = 1.0f;
                m_IsFading = false;  // フェードイン完了
            }
        }
        else {
            m_Opacity -= 0.05f;  // フェードアウトの速さ
            if (m_Opacity <= 0.0f) {
                m_Opacity = 0.0f;
                m_IsFading = false;  // フェードアウト完了
            }
        }

        // 不透明度をマテリアルに反映
        m_Material.SetDiffuse(Color(1.0f, 1.0f, 1.0f, m_Opacity));
        m_Material.SetGPU();
    }
}

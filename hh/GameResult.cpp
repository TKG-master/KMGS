#include "GameResult.h"

using namespace DirectX::SimpleMath;

void GameUI::Init(std::string TexPaht)
{
	// シェーダオブジェクト生成
	m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");

	// マテリアル生成
	MATERIAL	rmtrl;
	rmtrl.Ambient = Color(0, 0, 0, 0);
	rmtrl.Diffuse = Color(1, 1, 1, 1);
	rmtrl.Emission = Color(0, 0, 0, 0);
	rmtrl.Specular = Color(0, 0, 0, 0);
	rmtrl.Shiness = 0;
	rmtrl.TextureEnable = TRUE;

	m_Material.Create(rmtrl);



	m_Texture.Load(TexPaht);

}

void GameUI::Update()
{

}

void GameUI::Draw()
{

	Renderer::SetWorldViewProjection2D();
	ID3D11DeviceContext* devicecontext = Renderer::GetDeviceContext();

	m_Shader.SetGPU();
	m_Material.SetGPU();

	//長方形の４頂点の位置
	std::vector<VERTEX_3D> rectVertices(4);

	rectVertices[0].Position = Vector3(Center.x - halfWidth / 2, Center.y - halfHeight / 2, 0);
	rectVertices[1].Position = Vector3(Center.x + halfWidth / 2, Center.y - halfHeight / 2, 0);
	rectVertices[2].Position = Vector3(Center.x - halfWidth / 2, Center.y + halfHeight / 2, 0);
	rectVertices[3].Position = Vector3(Center.x + halfWidth / 2, Center.y + halfHeight / 2, 0);

	rectVertices[0].TexCoord = Vector2(0, 0);
	rectVertices[1].TexCoord = Vector2(1, 0);
	rectVertices[2].TexCoord = Vector2(0, 1);
	rectVertices[3].TexCoord = Vector2(1, 1);

	for (int i = 0; i < 4; ++i)
	{
		rectVertices[i].Diffuse = color;
	}

	//シェーダーにセット
	m_VertexBuffer.Create(rectVertices);
	m_VertexBuffer.SetGPU();
	m_Texture.SetGPU();

	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	devicecontext->Draw(4, 0);
}

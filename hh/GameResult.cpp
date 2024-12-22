#include "GameResult.h"
#include "Camera.h"

using namespace DirectX::SimpleMath;

GameUI::GameUI()
{

}

GameUI::~GameUI()
{

}

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

void GameUI::Update(DirectX::SimpleMath::Matrix viewM, DirectX::SimpleMath::Matrix ProjM)
{
	// カメラからビュー行列とプロジェクション行列を取得
	DirectX::SimpleMath::Matrix viewMatrix = viewM;  // カメラクラスのGetViewMatrix()を使用
	DirectX::SimpleMath::Matrix projectionMatrix = ProjM;  // カメラクラスのGetProjectionMatrix()を使用

	// 3Dのワールド空間座標 (例：UIの中央位置)
	DirectX::SimpleMath::Vector3 worldPosition(Center.x, Center.y, 0.0f);

	// ワールド、ビュー、プロジェクション行列を使ってスクリーン座標に変換
	DirectX::SimpleMath::Vector4 screenPosition = DirectX::XMVector4Transform(DirectX::SimpleMath::Vector4(worldPosition.x, worldPosition.y, worldPosition.z, 1.0f), viewMatrix * projectionMatrix);

	// NDC (正規化デバイス座標)からスクリーン座標へ変換
	screenPosition.x /= screenPosition.w;
	screenPosition.y /= screenPosition.w;

	// スクリーン座標に変換された結果をUIの中央位置に設定
	Center.x = (screenPosition.x + 1.0f) * 0.5f * 1920;
	Center.y = (1.0f - screenPosition.y) * 0.5f * 1080; // Y軸が反転している場合
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

void GameUI::SetFadePos(DirectX::SimpleMath::Vector3 Fadepos)
{
	this->Center.x = Fadepos.x;
	this->Center.y = Fadepos.z;
}

DirectX::SimpleMath::Vector3 GameUI::GetFadePos()
{
	DirectX::SimpleMath::Vector3 Fadepos;
	Fadepos.x = this->Center.x;
	Fadepos.z = this->Center.y;

	return Fadepos;

}

void GameUI::SetPosition(DirectX::SimpleMath::Vector3 position)
{
	// 3D空間上の座標をUIの中央位置として設定
	Center.x = position.x;
	Center.y = position.y;
}

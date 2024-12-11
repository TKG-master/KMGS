#include	"Polygon2D.h"

using namespace DirectX::SimpleMath;

void Polygon2D::Init(std::string TexPath)
{
	// 頂点データ
	std::vector<VERTEX_3D>	vertices;

	vertices.resize(4);

	vertices[0].Position = Vector3(0.0, -500, 0);	//左下
	vertices[1].Position = Vector3(1500,-500, 0);		//右下
	vertices[2].Position = Vector3(0.0, 500, 0);	//左上
	vertices[3].Position = Vector3(500, 500, 0);	//右上

	vertices[0].Diffuse = Color(1, 1, 1, 1);
	vertices[1].Diffuse = Color(1, 1, 1, 1);
	vertices[2].Diffuse = Color(1, 1, 1, 1);
	vertices[3].Diffuse = Color(1, 1, 1, 1);

	vertices[0].TexCoord = Vector2(0, 0);
	vertices[1].TexCoord = Vector2(1, 0);
	vertices[2].TexCoord = Vector2(0, 1);
	vertices[3].TexCoord = Vector2(1, 1);

	// 頂点バッファ生成
	m_VertexBuffer.Create(vertices);

	// インデックスバッファ生成
	std::vector<unsigned int> indices;
	indices.resize(4);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	// インデックスバッファ生成
	m_IndexBuffer.Create(indices);

	// シェーダオブジェクト生成
	m_Shader.Create("shader/unlitTextureVS.hlsl","shader/unlitTexturePS.hlsl");

	// マテリアル生成
	MATERIAL	mtrl;
	mtrl.Ambient = Color(0, 0, 0, 0);
	mtrl.Diffuse = Color(1, 1, 1, 1);
	mtrl.Emission = Color(0, 0, 0, 0);
	mtrl.Specular = Color(0, 0, 0, 0);
	mtrl.Shiness = 0;
	mtrl.TextureEnable = TRUE;

	m_Material.Create(mtrl);

	// テクスチャロード
	bool sts = m_Texture.Load(TexPath);
	assert(sts == true);
}

void Polygon2D::Update()
{
	// 頂点データ
	std::vector<VERTEX_3D>	vertices;

	vertices.resize(4);

	vertices[0].Position = Vector3(0, 50, 0);
	vertices[1].Position = Vector3(200, 50, 0);
	vertices[2].Position = Vector3(0, 250, 0);
	vertices[3].Position = Vector3(200, 250, 0);

	vertices[0].Diffuse = Color(1, 1, 1, 1);
	vertices[1].Diffuse = Color(1, 1, 1, 1);
	vertices[2].Diffuse = Color(1, 1, 1, 1);
	vertices[3].Diffuse = Color(1, 1, 1, 1);

	static int animcnt = 0;
	static int loopcnt = 0;

	float diffx = 1.0f / 3.0f;

	// 頂点データ書き換え
	vertices[0].TexCoord.x = 0.0f + diffx * animcnt;
	vertices[0].TexCoord.y = 0.0f;

	vertices[1].TexCoord.x = 1.0f / 3.0f + diffx * animcnt;
	vertices[1].TexCoord.y = 0.0f;

	vertices[2].TexCoord.x = 0.0f + diffx * animcnt;
	vertices[2].TexCoord.y = 1.0f / 4.0f;

	vertices[3].TexCoord.x = 1.0f / 3.0f + diffx * animcnt;
	vertices[3].TexCoord.y = 1.0f / 4.0f;

	m_VertexBuffer.Modify(vertices);

	// アニメーション切り替え時間調整
	loopcnt++;

	if (loopcnt % 10 == 0) {
		animcnt++;
		animcnt = animcnt % 3;
	}
}

void Polygon2D::Draw()
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

void Polygon2D::Dispose()
{

}
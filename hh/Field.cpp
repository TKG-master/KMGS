#include "Field.h"

using namespace DirectX::SimpleMath;

void Field::Init()
{
	//頂点データ
	std::vector<VERTEX_3D> vertices;
	vertices.resize(8);
	vertices[0].Position = Vector3(0, -3000, 0);		//左上
	vertices[1].Position = Vector3(800, -3000,0);		//右上
	vertices[2].Position = Vector3(0, -3000, -1200);	//左下
	vertices[3].Position = Vector3(800, -3000, -1200);	//右下



	vertices[0].Diffuse = Color(1, 1, 1, 1);
	vertices[1].Diffuse = Color(1, 1, 1, 1);
	vertices[2].Diffuse = Color(1, 1, 1, 1);
	vertices[3].Diffuse = Color(1, 1, 1, 1);

	vertices[0].TexCoord = Vector2(0, 0);
	vertices[1].TexCoord = Vector2(1, 0);
	vertices[2].TexCoord = Vector2(0, 1);
	vertices[3].TexCoord = Vector2(1, 1);

	//頂点バッファ生成
	m_VertexBuffer.Create(vertices);
	//インデックスバッファ生成
	std::vector<unsigned int> indices;
	indices.resize(24);
	//下の面
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;


	//インデックスバッファ生成
	m_IndexBuffer.Create(indices);
	//シェーダーオブジェクト生成
		m_Shader.Create("shader/unlitTextureVS.hlsl","shader/unlitTexturePS.hlsl");
	//マテリアル生成
	MATERIAL mtrl;
	mtrl.Ambient = Color(0, 0, 0, 0);
	mtrl.Diffuse = Color(1, 1, 1, 1);
	mtrl.Emission = Color(0, 0, 0, 0);
	mtrl.Specular = Color(0, 0, 0, 0);
	mtrl.Shiness = 0;
	mtrl.TextureEnable = TRUE;
	m_Material.Create(mtrl);
	////テクスチャロード
	bool sts = m_Texture.Load("assets\\siro.jpg");
	assert(sts == true);

	

}

void Field::Draw()
{
	//SRT情報作成
	Matrix r =
		Matrix::CreateFromYawPitchRoll(
			m_Rotation.y,
			m_Rotation.x,
			m_Rotation.z
		);

	Matrix t = Matrix::CreateTranslation(
		m_Position.x,
		m_Position.y,
		m_Position.z
	);

	Matrix s = Matrix::CreateScale(
		m_Scale.x,
		m_Scale.y,
		m_Scale.z
	);

	Matrix worldmtx;

	worldmtx = s * r * t;

	//m_Rotation.y += 0.01f;

	Renderer::SetWorldMatrix(&worldmtx);	//GPUにセット

	//描画の処理
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();

	//トポロジーをセット（旧プリミティブタイプ）
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();

	m_Material.SetGPU();
	m_Texture.SetGPU();

	devicecontext->DrawIndexed(
		4,				//描画するインデックス数
		0,				//最初のインデックスバッファの位置
		0
	);


}

void Field::Dispose()
{
}

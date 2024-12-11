#include "PlayerTest.h"

using namespace DirectX::SimpleMath;

using namespace DirectX;

PlayerTest::PlayerTest()
{
	this->Init();
}

PlayerTest::~PlayerTest()
{

}

void PlayerTest::Update()
{
	if (Input::Get()->GetKeyPress(DIK_A))
	{

		if (forward.x != -1)
		{
			forward.x = -1;
		}
		this->m_Position.x += this->GetForward().x * this->Move(this->GetSpeed());
	}
	else if (Input::Get()->GetKeyPress(DIK_D))
	{
		if (forward.x != 1)
		{
			forward.x = 1;
		}
		this->m_Position.x += this->GetForward().x * this->Move(this->GetSpeed());
	}
	if(Input::Get()->GetKeyPress(DIK_W))
	{
		//上
		if (forward.z != 1)
		{
			forward.z = 1;
		}
		this->m_Position.z += this->GetForward().z * this->Move(this->GetSpeed());

	}
	else if(Input::Get()->GetKeyPress(DIK_S))
	{
		//下
		if (forward.z != -1)
		{
			forward.z = -1;
		}
		this->m_Position.z += this->GetForward().z * this->Move(this->GetSpeed());

	}
}

void PlayerTest::Init()
{
	//頂点データ
	std::vector<VERTEX_3D> vertices;
	vertices.resize(8);
	vertices[0].Position = Vector3(-5, 10, -5);
	vertices[1].Position = Vector3(5, 10, -5);
	vertices[2].Position = Vector3(-5, 0, -5);
	vertices[3].Position = Vector3(5, 0, -5);
	vertices[4].Position = Vector3(-5, 10, 5);
	vertices[5].Position = Vector3(5, 10, 5);
	vertices[6].Position = Vector3(-5, 0, 5);
	vertices[7].Position = Vector3(5, 0, 5);
	vertices[0].Diffuse = Color(1, 1, 1, 1);
	vertices[1].Diffuse = Color(1, 1, 1, 1);
	vertices[2].Diffuse = Color(1, 1, 1, 1);
	vertices[3].Diffuse = Color(1, 1, 1, 1);
	vertices[4].Diffuse = Color(1, 1, 1, 1);
	vertices[5].Diffuse = Color(1, 1, 1, 1);
	vertices[6].Diffuse = Color(1, 1, 1, 1);
	vertices[7].Diffuse = Color(1, 1, 1, 1);

	vertices[0].TexCoord = Vector2(0, 0);
	vertices[1].TexCoord = Vector2(1, 0);
	vertices[2].TexCoord = Vector2(0, 1);
	vertices[3].TexCoord = Vector2(1, 1);

	vertices[1].TexCoord = Vector2(0, 0);
	vertices[5].TexCoord = Vector2(1, 0);
	vertices[3].TexCoord = Vector2(0, 1);
	vertices[7].TexCoord = Vector2(1, 1);

	vertices[4].TexCoord = Vector2(0, 0);
	vertices[0].TexCoord = Vector2(1, 0);
	vertices[6].TexCoord = Vector2(0, 1);
	vertices[2].TexCoord = Vector2(1, 1);

	vertices[7].TexCoord = Vector2(0, 0);
	vertices[6].TexCoord = Vector2(1, 0);
	vertices[3].TexCoord = Vector2(0, 1);
	vertices[2].TexCoord = Vector2(1, 1);

	vertices[5].TexCoord = Vector2(0, 0);
	vertices[4].TexCoord = Vector2(1, 0);
	vertices[7].TexCoord = Vector2(0, 1);
	vertices[6].TexCoord = Vector2(1, 1);

	vertices[4].TexCoord = Vector2(0, 0);
	vertices[5].TexCoord = Vector2(1, 0);
	vertices[0].TexCoord = Vector2(0, 1);
	vertices[1].TexCoord = Vector2(1, 1);



	//頂点バッファ生成
	m_VertexBuffer.Create(vertices);
	//インデックスバッファ生成
	std::vector<unsigned int> indices;
	indices.resize(24);
	//正面の面
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;
	//左側の面
	indices[4] = 1;
	indices[5] = 5;
	indices[6] = 3;
	indices[7] = 7;
	//右側の面
	indices[8] = 4;
	indices[9] = 0;
	indices[10] = 6;
	indices[11] = 2;
	//下側の面
	indices[12] = 7;
	indices[13] = 6;
	indices[14] = 3;
	indices[15] = 2;
	//後ろの面
	indices[16] = 5;
	indices[17] = 4;
	indices[18] = 7;
	indices[19] = 6;
	//真上の面
	indices[20] = 4;
	indices[21] = 5;
	indices[22] = 0;
	indices[23] = 1;
	//インデックスバッファ生成
	m_IndexBuffer.Create(indices);
	//シェーダーオブジェクト生成
	m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");
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

float PlayerTest::GetSpeed()
{
	return this->movespeed;
}

float PlayerTest::Move(float a)
{
	return a;
}

DirectX::XMFLOAT3 PlayerTest::GetForward()
{
	return forward;
}

DirectX::SimpleMath::Vector3 PlayerTest::GetPosition()
{
	return this->m_Position;
}

DirectX::SimpleMath::Vector3 PlayerTest::GetRoatation()
{
	return this->m_Rotation;
}

DirectX::SimpleMath::Vector3 PlayerTest::GetScale()
{
	return this->m_Scale;
}

void PlayerTest::SetPosition(DirectX::SimpleMath::Vector3 pos)
{
	this->m_Position = pos;
}

void PlayerTest::SetRoatation(DirectX::SimpleMath::Vector3 roa)
{
	this->m_Rotation = roa;
}

void PlayerTest::SetScale(DirectX::SimpleMath::Vector3 sca)
{
	this->m_Scale = sca;
}

void PlayerTest::Draw()
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
	devicecontext->DrawIndexed(
		4,				//描画するインデックス数
		4,				//最初のインデックスバッファの位置
		0
	);
	devicecontext->DrawIndexed(
		4,				//描画するインデックス数
		8,				//最初のインデックスバッファの位置
		0
	);
	devicecontext->DrawIndexed(
		4,				//描画するインデックス数
		12,				//最初のインデックスバッファの位置
		0
	);
	devicecontext->DrawIndexed(
		4,				//描画するインデックス数
		16,				//最初のインデックスバッファの位置
		0
	);

	devicecontext->DrawIndexed(
		4,				//描画するインデックス数
		20,				//最初のインデックスバッファの位置
		0
	);
}

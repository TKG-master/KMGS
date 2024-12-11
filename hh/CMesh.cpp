#include "CMesh.h"

void CMesh::ModifyRotation()
{
	if (m_Rotation.x < 0)
	{
		m_Rotation.x = 359;
	}
	if (m_Rotation.y < 0)
	{
		m_Rotation.y = 359;
	}
	if (m_Rotation.z < 0)
	{
		m_Rotation.z = 359;
	}

	if (m_Rotation.x >= 360)
	{
		m_Rotation.x = 0;
	}
	if (m_Rotation.y >= 360)
	{
		m_Rotation.y = 0;
	}
	if (m_Rotation.z >= 360)
	{
		m_Rotation.z = 0;
	}
}

void CMesh::Init()
{
	m_VertexBuffer.Create(m_vertices);
	m_IndexBuffer.Create(m_indices);
}

void CMesh::Update()
{

	//SRT情報
	DirectX::SimpleMath::Matrix r = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(m_Rotation.y), // Yaw (度数 → ラジアン)
		DirectX::XMConvertToRadians(m_Rotation.x), // Pitch (度数 → ラジアン)
		DirectX::XMConvertToRadians(m_Rotation.z)  // Roll (度数 → ラジアン)
	);
	DirectX::SimpleMath::Matrix t = DirectX::SimpleMath::Matrix::CreateTranslation(
		m_Position.x,
		m_Position.y,
		m_Position.z
	);
	DirectX::SimpleMath::Matrix s = DirectX::SimpleMath::Matrix::CreateScale(
		m_Scale.x,
		m_Scale.y,
		m_Scale.z
	);

	worldmtx = s * r * t;
}

void CMesh::Draw()
{

	Renderer::SetWorldMatrix(&worldmtx);

	ID3D11DeviceContext* deviceContext;
	deviceContext = Renderer::GetDeviceContext();

	//トポロジーをセット
	deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();

	m_Material.SetGPU();
	m_Texture.SetGPU();

	deviceContext->DrawIndexed(static_cast<int>(m_indices.size()), 0, 0);
}

void CMesh::DrawSubset(unsigned int indexnum, unsigned int baseindex, unsigned int basevertexindex)
{
	Renderer::GetDeviceContext()->DrawIndexed(
		indexnum,								// 描画するインデックス数（面数×３）
		baseindex,								// 最初のインデックスバッファの位置
		basevertexindex);						// 頂点バッファの最初から使う
}


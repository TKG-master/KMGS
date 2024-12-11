#pragma once
#include	<vector>
#include	<SimpleMath.h>
#include	<simplemath.h>
#include	"renderer.h"

#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CMaterial.h"
#include "CTexture.h"
class CMesh {
protected:
	std::vector<VERTEX_3D>		m_vertices;		// 頂点座標群
	std::vector<unsigned int>	m_indices;		// インデックスデータ群

	CVertexBuffer<VERTEX_3D>	m_VertexBuffer;		//頂点バッファ
	CIndexBuffer				m_IndexBuffer;		//インデックスバッファ
	CShader					m_Shader;			//シェーダー
	CMaterial				m_Material;			//マテリアル
	CTexture					m_Texture;			//テクスチャ

	DirectX::SimpleMath::Matrix worldmtx;		// ワールドマトリックス

	// SRT情報
	DirectX::SimpleMath::Vector3 m_Position = { 0,0,0 };
	DirectX::SimpleMath::Vector3 m_Rotation = { 0,0,0 };
	DirectX::SimpleMath::Vector3 m_Scale = { 1.0f,1.0f,1.0f };
public:


	// 頂点データ取得
	const std::vector<VERTEX_3D>& GetVertices() { return m_vertices; }
	// インデックスデータ取得
	const std::vector<unsigned int>& GetIndices() { return m_indices; }
	// 頂点バッファを更新
	void Modify(const std::vector<VERTEX_3D>& vertices) { m_VertexBuffer.Modify(vertices); }

	void SetPosition(DirectX::SimpleMath::Vector3 pos) { m_Position = pos; };
	DirectX::SimpleMath::Vector3 GetPosition() { return m_Position; };

	void SetRotation(DirectX::SimpleMath::Vector3 rot) { m_Rotation = rot; };
	DirectX::SimpleMath::Vector3 GetRotation() { return m_Rotation; };

	void SetScale(DirectX::SimpleMath::Vector3 pos) { m_Scale = pos; };
	DirectX::SimpleMath::Vector3 GetScale() { return m_Scale; };


	//回転後に使用：角度の修正
	void ModifyRotation();

	// 初期化
	virtual void Init();
	// 更新
	virtual void Update();
	// 描画
	virtual void Draw();
	// サブセット描画
	virtual void DrawSubset(unsigned int indexnum, unsigned int baseindex, unsigned int basevertexindex);

};


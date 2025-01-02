#include "CFBXMesh.h"
#include <iostream>
using namespace DirectX::SimpleMath;

FBXMesh::FBXMesh()
{

}

FBXMesh::~FBXMesh()
{

}

void FBXMesh::Init()
{
	// メッシュ読み込み
	CStaticMesh staticmesh;

	std::vector<std::string> filename =
	{
		"assets/model/book",
	};

	std::vector<std::string> texdirectory =
	{
		"assets/model/book"
	};

	// u8stringをstringに変換
	std::u8string u8str = u8"assets/model/book/book.obj";  //ok
	//std::u8string u8str = u8"assets/model/グリン子レギュ1.0/グリン子レギュ1.0.pmx";   //ng

	std::string str(reinterpret_cast<const char*>(u8str.c_str()), u8str.size());

	staticmesh.Load(str, texdirectory[0]);

	g_MeshRenderer.Init(staticmesh);

	// シェーダオブジェクト生成
	g_Shader.Create("shader/vertexLightingVS.hlsl", "shader/vertexLightingPS.hlsl");

	// サブセット情報取得
	g_subsets = staticmesh.GetSubsets();

	// diffuseテクスチャ情報取得
	g_DiffuseTextures = staticmesh.GetDiffuseTextures();

	// マテリアル情報取得	
	std::vector<MATERIAL> materials = staticmesh.GetMaterials();

	// マテリアル数分ループ
	for (int i = 0; i < materials.size(); i++)
	{
		// マテリアルオブジェクト生成
		std::unique_ptr<CMaterial> m = std::make_unique<CMaterial>();

		// マテリアル情報をセット
		m->Create(materials[i]);

		// マテリアルオブジェクトを配列に追加
		g_Materiales.push_back(std::move(m));
	}
}

void FBXMesh::UnInit()
{

}

void FBXMesh::Draw()
{
	Matrix rmtx = Matrix::CreateFromYawPitchRoll(rot.y, rot.x, rot.z);
	Matrix smtx = Matrix::CreateScale(scale.x, scale.y, scale.z);
	Matrix tmtx = Matrix::CreateTranslation(pos.x, pos.y, pos.z);

	Matrix wmtx = smtx * rmtx * tmtx;

	Renderer::SetWorldMatrix(&wmtx);

	g_Shader.SetGPU();

	// インデックスバッファ・頂点バッファをセット
	g_MeshRenderer.BeforeDraw();

	// マテリアル数分ループ 
	for (int i = 0; i < g_subsets.size(); i++)
	{
		// マテリアルをセット(サブセット情報の中にあるマテリアルインデックを使用する)
		g_Materiales[g_subsets[i].MaterialIdx]->SetGPU();

		if (g_Materiales[g_subsets[i].MaterialIdx]->isDiffuseTextureEnable())
		{
			g_DiffuseTextures[g_subsets[i].MaterialIdx]->SetGPU();
		}

		g_MeshRenderer.DrawSubset(
			g_subsets[i].IndexNum,							// 描画するインデックス数
			g_subsets[i].IndexBase,							// 最初のインデックスバッファの位置	
			g_subsets[i].VertexBase);						// 頂点バッファの最初から使用
	}
}

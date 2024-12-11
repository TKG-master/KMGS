#pragma once

#include "CStaticMesh.h"
#include "AssimpPerse.h"
#include "CTreeNode.h"	
#include "renderer.h"
#include "BoneCombMatrix.h"
#include "CStaticMeshRenderer.h"

class CAnimationMesh : public CStaticMesh
{
	// ボーン辞書
	std::unordered_map<std::string, BONE> m_BoneDictionary{};	// 20240714 DX化

	// カレントのアニメーションデータ
	aiAnimation* m_CurrentAnimation{};

	aiAnimation* m_FromAnimation{};
	aiAnimation* m_ToAnimation{};

	// assimp ノード名ツリー（親子関係がわかる）
	CTreeNode<std::string>	m_AssimpNodeNameTree{};

	// レンダラ
	CStaticMeshRenderer m_StaticMeshRenderer{};

public:
	void SetCurentAnimation(aiAnimation* currentanimation);
	void SetFromAnimation(aiAnimation* animation)
	{
		m_FromAnimation = animation;
	}
	void SetToAnimation(aiAnimation* animation)
	{
		m_ToAnimation = animation;
	}

	void Load(std::string filename, std::string texturedirectory = "");

	// 階層構造を考慮したボーンコンビネーション行列を更新
	void UpdateBoneMatrix(CTreeNode<std::string>* ptree, DirectX::SimpleMath::Matrix matrix);		// 20240714 DX化	

	// アニメーションの更新
	void Update(BoneCombMatrix& bonecombarray, int& CurrentFrame);

	// アニメーションの更新（モーションブレンド）
	void BlendUpdate(
		BoneCombMatrix& bonecombarray,			// ボーンコンビネーション行列と現在のフレーム	
		int fromframe, 							// FROM側のモーション名とフレーム
		int toframe,							// TO側のモーション名とフレーム
		float blendarate);						// 割合

	// 描画
	void Draw();
};

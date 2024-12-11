#include	<iostream>
#include	"CAnimationMesh.h"
#include	"utility.h"

using namespace DirectX::SimpleMath;

void CAnimationMesh::SetCurentAnimation(aiAnimation* currentanimation) {
	m_CurrentAnimation = currentanimation;
}

// ノードツリー表示(debug用)
static void DispNodeTree(CTreeNode<std::string>* ptree)
{
	std::cout << ptree->m_nodedata << std::endl;

	for (unsigned int n = 0; n < ptree->m_children.size(); n++)
	{
		DispNodeTree(ptree->m_children[n].get());
	}
}

void CAnimationMesh::Draw()
{
	// メッシュ描画
	m_StaticMeshRenderer.Draw();
}


void CAnimationMesh::Load(std::string filename, std::string texturedirectory)
{
	// メッシュ読み込み
	CStaticMesh::Load(filename, texturedirectory);

	// アニメーションデータ(ASSIMP用）
	std::unordered_map<std::string, AssimpPerse::BONE> assimp_BoneDictionary{};			// 20240714 DX化

	// ボーン辞書取得（ボーン名をキーにしてボーン情報が取れる）
	assimp_BoneDictionary = AssimpPerse::GetBoneDictionary();							// 20240714 DX化

	for (auto& asimpbone : assimp_BoneDictionary) {										// 20240714 DX化
		BONE dxbone;																	// 20240714 DX化	

		dxbone.meshname = asimpbone.second.meshname;									// 20240714 DX化
		dxbone.armaturename = asimpbone.second.armaturename;							// 20240714 DX化
		dxbone.bonename = asimpbone.second.bonename;									// 20240714 DX化
		dxbone.idx = asimpbone.second.idx;												// 20240714 DX化

		dxbone.OffsetMatrix = utility::aiMtxToDxMtx(asimpbone.second.OffsetMatrix);
		dxbone.AnimationMatrix = Matrix::Identity;										// 20240714 DX化
		dxbone.Matrix = Matrix::Identity;												// 20240714 DX化

		dxbone.weights.clear();															// 20240714 DX化
		for (auto& asimpweight : asimpbone.second.weights)								// 20240714 DX化	
		{
			WEIGHT dxweight;															// 20240714 DX化			
			dxweight.bonename = asimpweight.bonename;									// 20240714 DX化
			dxweight.meshname = asimpweight.meshname;									// 20240714 DX化
			dxweight.vertexindex = asimpweight.vertexindex;								// 20240714 DX化
			dxweight.weight = asimpweight.weight;										// 20240714 DX化
			dxbone.weights.push_back(dxweight);											// 20240714 DX化		
		}																				// 20240714 DX化

		m_BoneDictionary[asimpbone.first] = dxbone;										// 20240714 DX化
	}

	// ボーン名ツリー取得
	m_AssimpNodeNameTree = AssimpPerse::GetBoneNameTree();

	// レンダラ初期化
	m_StaticMeshRenderer.Init(*this);

}

// 階層構造を考慮したボーンコンビネーション行列を更新
void CAnimationMesh::UpdateBoneMatrix(
	CTreeNode<std::string>* ptree,
	Matrix matrix)															// 20240714 DX化	
{
	// ノード名からボーン辞書を使ってボーン情報を取得
	BONE* bone = &m_BoneDictionary[ptree->m_nodedata];						// 20240714 DX化		

	Matrix bonecombination;													// 20240714 DX化；

	// ボーンオフセット行列×ボーンアニメメーション行列×逆ボーンオフセット行列
	bonecombination = bone->OffsetMatrix * bone->AnimationMatrix * matrix;	// 20240714 DX化
	bone->Matrix = bonecombination;											// 20240714 DX化

	// 自分の姿勢を表す行列を作成
	Matrix mybonemtx;														// 20240714 DX化
	mybonemtx = bone->AnimationMatrix * matrix;								// 20240714 DX化
	// 子ノードに対して再帰的に処理											// 20240714 DX化
	for (unsigned int n = 0; n < ptree->m_children.size(); n++)				// 20240714 DX化
	{																		// 20240714 DX化
		UpdateBoneMatrix(ptree->m_children[n].get(), mybonemtx);			// 20240714 DX化
	}																		// 20240714 DX化
}

// アニメーションの更新
void CAnimationMesh::Update(BoneCombMatrix& bonecombarray, int& CurrentFrame)
{
	// アニメーションデータ取得
	aiAnimation* animation = m_CurrentAnimation;

	// ボーン数分ループしてボーン行列を作成
	for (unsigned int c = 0; c < animation->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim = animation->mChannels[c];

		// ノード名からボーン辞書を使ってassimpのボーン情報を取得
		BONE* bone = &(m_BoneDictionary[nodeAnim->mNodeName.C_Str()]);	// 20240714 DX化	

		int f;

		f = CurrentFrame % nodeAnim->mNumRotationKeys;				//簡易実装
		aiQuaternion rot = nodeAnim->mRotationKeys[f].mValue;

		f = CurrentFrame % nodeAnim->mNumPositionKeys;				//簡易実装
		aiVector3D pos = nodeAnim->mPositionKeys[f].mValue;

		// SRTから行列を生成
		Vector3 s = { 1.0f,1.0f,1.0f };		// 20240714 DX化
		Vector3 t = { pos.x,pos.y,pos.z };	// 20240714 DX化
		Quaternion r{};						// 20240714 DX化

		r.x = rot.x;						// 20240714 DX化
		r.y = rot.y;						// 20240714 DX化
		r.z = rot.z;						// 20240714 DX化
		r.w = rot.w;						// 20240714 DX化

		Matrix scalemtx = Matrix::CreateScale(s.x, s.y, s.z);		// 20240714 DX化
		Matrix rotmtx = Matrix::CreateFromQuaternion(r);			// 20240714 DX化
		Matrix transmtx = Matrix::CreateTranslation(t.x, t.y, t.z);	// 20240714 DX化

		bone->AnimationMatrix = scalemtx * rotmtx * transmtx;		// 20240714 DX化
	}

	UpdateBoneMatrix(&m_AssimpNodeNameTree, Matrix::Identity);		// 20240714 DX化	

	// ボーンコンビネーション行列の配列をセット
	for (const auto& bone : m_BoneDictionary)
	{
		bonecombarray.ConstantBufferMemory.BoneCombMtx[bone.second.idx] = bone.second.Matrix.Transpose();	// 20240714 DX化
	}
}

// アニメーションの更新
void CAnimationMesh::BlendUpdate(
	BoneCombMatrix& bonecombarray,			// ボーンコンビネーション行列と現在のフレーム	
	int fromframe, 							// FROM側のモーション名とフレーム
	int toframe,							// TO側のモーション名とフレーム
	float blendarate)						// 割合
{
	// アニメーションデータ取得
	aiAnimation* fromanimation = m_FromAnimation;

	// ボーン数分ループしてボーン行列を作成
	for (unsigned int c = 0; c < fromanimation->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim = fromanimation->mChannels[c];

		// ノード名からボーン辞書を使ってassimpのボーン情報を取得
		BONE* bone = &(m_BoneDictionary[nodeAnim->mNodeName.C_Str()]);

		int f;

		f = fromframe % nodeAnim->mNumRotationKeys;				//簡易実装
		aiQuaternion rot = nodeAnim->mRotationKeys[f].mValue;

		f = fromframe % nodeAnim->mNumPositionKeys;				//簡易実装
		aiVector3D pos = nodeAnim->mPositionKeys[f].mValue;

		bone->fromPos.x = pos.x;
		bone->fromPos.y = pos.y;
		bone->fromPos.z = pos.z;

		bone->fromScale.x = 1.0f;
		bone->fromScale.y = 1.0f;
		bone->fromScale.z = 1.0f;

		bone->fromQuat.x = rot.x;
		bone->fromQuat.y = rot.y;
		bone->fromQuat.z = rot.z;
		bone->fromQuat.w = rot.w;
	}

	// アニメーションデータ取得
	aiAnimation* toanimation = m_ToAnimation;

	// ボーン数分ループしてボーン行列を作成
	for (unsigned int c = 0; c < toanimation->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim = toanimation->mChannels[c];

		// ノード名からボーン辞書を使ってassimpのボーン情報を取得
		BONE* bone = &(m_BoneDictionary[nodeAnim->mNodeName.C_Str()]);

		int f;

		f = toframe % nodeAnim->mNumRotationKeys;				//簡易実装
		aiQuaternion rot = nodeAnim->mRotationKeys[f].mValue;

		f = toframe % nodeAnim->mNumPositionKeys;				//簡易実装
		aiVector3D pos = nodeAnim->mPositionKeys[f].mValue;

		bone->toPos.x = pos.x;
		bone->toPos.y = pos.y;
		bone->toPos.z = pos.z;

		bone->toScale.x = 1.0f;
		bone->toScale.y = 1.0f;
		bone->toScale.z = 1.0f;

		bone->toQuat.x = rot.x;
		bone->toQuat.y = rot.y;
		bone->toQuat.z = rot.z;
		bone->toQuat.w = rot.w;
	}

	// ブレンドする
	// ボーン数分ループしてボーン行列を作成
	for (unsigned int c = 0; c < toanimation->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim = toanimation->mChannels[c];

		// ノード名からボーン辞書を使ってassimpのボーン情報を取得
		BONE* bone = &(m_BoneDictionary[nodeAnim->mNodeName.C_Str()]);

		Quaternion r = Quaternion::Slerp(bone->fromQuat, bone->toQuat, blendarate);
		Vector3 t = Vector3::Lerp(bone->fromPos, bone->toPos, blendarate);
		Vector3 s = Vector3::Lerp(bone->fromScale, bone->toScale, blendarate);

		Matrix scalemtx = Matrix::CreateScale(s.x, s.y, s.z);
		Matrix rotmtx = Matrix::CreateFromQuaternion(r);
		Matrix transmtx = Matrix::CreateTranslation(t.x, t.y, t.z);

		bone->AnimationMatrix = scalemtx * rotmtx * transmtx;
	}

	// ボーンコンビネーション行列をすべて再帰を使用して更新する
	UpdateBoneMatrix(&m_AssimpNodeNameTree, Matrix::Identity);

	// ボーンコンビネーション行列の配列をセット
	for (const auto& bone : m_BoneDictionary)
	{
		bonecombarray.ConstantBufferMemory.BoneCombMtx[bone.second.idx] = bone.second.Matrix.Transpose();
	}
}


#include	<iostream>
#include	"CAnimationMesh.h"
#include	"utility.h"

using namespace DirectX::SimpleMath;

void CAnimationMesh::SetCurentAnimation(aiAnimation* currentanimation) {
	m_CurrentAnimation = currentanimation;
}

// �m�[�h�c���[�\��(debug�p)
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
	// ���b�V���`��
	m_StaticMeshRenderer.Draw();
}


void CAnimationMesh::Load(std::string filename, std::string texturedirectory)
{
	// ���b�V���ǂݍ���
	CStaticMesh::Load(filename, texturedirectory);

	// �A�j���[�V�����f�[�^(ASSIMP�p�j
	std::unordered_map<std::string, AssimpPerse::BONE> assimp_BoneDictionary{};			// 20240714 DX��

	// �{�[�������擾�i�{�[�������L�[�ɂ��ă{�[����񂪎���j
	assimp_BoneDictionary = AssimpPerse::GetBoneDictionary();							// 20240714 DX��

	for (auto& asimpbone : assimp_BoneDictionary) {										// 20240714 DX��
		BONE dxbone;																	// 20240714 DX��	

		dxbone.meshname = asimpbone.second.meshname;									// 20240714 DX��
		dxbone.armaturename = asimpbone.second.armaturename;							// 20240714 DX��
		dxbone.bonename = asimpbone.second.bonename;									// 20240714 DX��
		dxbone.idx = asimpbone.second.idx;												// 20240714 DX��

		dxbone.OffsetMatrix = utility::aiMtxToDxMtx(asimpbone.second.OffsetMatrix);
		dxbone.AnimationMatrix = Matrix::Identity;										// 20240714 DX��
		dxbone.Matrix = Matrix::Identity;												// 20240714 DX��

		dxbone.weights.clear();															// 20240714 DX��
		for (auto& asimpweight : asimpbone.second.weights)								// 20240714 DX��	
		{
			WEIGHT dxweight;															// 20240714 DX��			
			dxweight.bonename = asimpweight.bonename;									// 20240714 DX��
			dxweight.meshname = asimpweight.meshname;									// 20240714 DX��
			dxweight.vertexindex = asimpweight.vertexindex;								// 20240714 DX��
			dxweight.weight = asimpweight.weight;										// 20240714 DX��
			dxbone.weights.push_back(dxweight);											// 20240714 DX��		
		}																				// 20240714 DX��

		m_BoneDictionary[asimpbone.first] = dxbone;										// 20240714 DX��
	}

	// �{�[�����c���[�擾
	m_AssimpNodeNameTree = AssimpPerse::GetBoneNameTree();

	// �����_��������
	m_StaticMeshRenderer.Init(*this);

}

// �K�w�\�����l�������{�[���R���r�l�[�V�����s����X�V
void CAnimationMesh::UpdateBoneMatrix(
	CTreeNode<std::string>* ptree,
	Matrix matrix)															// 20240714 DX��	
{
	// �m�[�h������{�[���������g���ă{�[�������擾
	BONE* bone = &m_BoneDictionary[ptree->m_nodedata];						// 20240714 DX��		

	Matrix bonecombination;													// 20240714 DX���G

	// �{�[���I�t�Z�b�g�s��~�{�[���A�j�����[�V�����s��~�t�{�[���I�t�Z�b�g�s��
	bonecombination = bone->OffsetMatrix * bone->AnimationMatrix * matrix;	// 20240714 DX��
	bone->Matrix = bonecombination;											// 20240714 DX��

	// �����̎p����\���s����쐬
	Matrix mybonemtx;														// 20240714 DX��
	mybonemtx = bone->AnimationMatrix * matrix;								// 20240714 DX��
	// �q�m�[�h�ɑ΂��čċA�I�ɏ���											// 20240714 DX��
	for (unsigned int n = 0; n < ptree->m_children.size(); n++)				// 20240714 DX��
	{																		// 20240714 DX��
		UpdateBoneMatrix(ptree->m_children[n].get(), mybonemtx);			// 20240714 DX��
	}																		// 20240714 DX��
}

// �A�j���[�V�����̍X�V
void CAnimationMesh::Update(BoneCombMatrix& bonecombarray, int& CurrentFrame)
{
	// �A�j���[�V�����f�[�^�擾
	aiAnimation* animation = m_CurrentAnimation;

	// �{�[���������[�v���ă{�[���s����쐬
	for (unsigned int c = 0; c < animation->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim = animation->mChannels[c];

		// �m�[�h������{�[���������g����assimp�̃{�[�������擾
		BONE* bone = &(m_BoneDictionary[nodeAnim->mNodeName.C_Str()]);	// 20240714 DX��	

		int f;

		f = CurrentFrame % nodeAnim->mNumRotationKeys;				//�ȈՎ���
		aiQuaternion rot = nodeAnim->mRotationKeys[f].mValue;

		f = CurrentFrame % nodeAnim->mNumPositionKeys;				//�ȈՎ���
		aiVector3D pos = nodeAnim->mPositionKeys[f].mValue;

		// SRT����s��𐶐�
		Vector3 s = { 1.0f,1.0f,1.0f };		// 20240714 DX��
		Vector3 t = { pos.x,pos.y,pos.z };	// 20240714 DX��
		Quaternion r{};						// 20240714 DX��

		r.x = rot.x;						// 20240714 DX��
		r.y = rot.y;						// 20240714 DX��
		r.z = rot.z;						// 20240714 DX��
		r.w = rot.w;						// 20240714 DX��

		Matrix scalemtx = Matrix::CreateScale(s.x, s.y, s.z);		// 20240714 DX��
		Matrix rotmtx = Matrix::CreateFromQuaternion(r);			// 20240714 DX��
		Matrix transmtx = Matrix::CreateTranslation(t.x, t.y, t.z);	// 20240714 DX��

		bone->AnimationMatrix = scalemtx * rotmtx * transmtx;		// 20240714 DX��
	}

	UpdateBoneMatrix(&m_AssimpNodeNameTree, Matrix::Identity);		// 20240714 DX��	

	// �{�[���R���r�l�[�V�����s��̔z����Z�b�g
	for (const auto& bone : m_BoneDictionary)
	{
		bonecombarray.ConstantBufferMemory.BoneCombMtx[bone.second.idx] = bone.second.Matrix.Transpose();	// 20240714 DX��
	}
}

// �A�j���[�V�����̍X�V
void CAnimationMesh::BlendUpdate(
	BoneCombMatrix& bonecombarray,			// �{�[���R���r�l�[�V�����s��ƌ��݂̃t���[��	
	int fromframe, 							// FROM���̃��[�V�������ƃt���[��
	int toframe,							// TO���̃��[�V�������ƃt���[��
	float blendarate)						// ����
{
	// �A�j���[�V�����f�[�^�擾
	aiAnimation* fromanimation = m_FromAnimation;

	// �{�[���������[�v���ă{�[���s����쐬
	for (unsigned int c = 0; c < fromanimation->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim = fromanimation->mChannels[c];

		// �m�[�h������{�[���������g����assimp�̃{�[�������擾
		BONE* bone = &(m_BoneDictionary[nodeAnim->mNodeName.C_Str()]);

		int f;

		f = fromframe % nodeAnim->mNumRotationKeys;				//�ȈՎ���
		aiQuaternion rot = nodeAnim->mRotationKeys[f].mValue;

		f = fromframe % nodeAnim->mNumPositionKeys;				//�ȈՎ���
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

	// �A�j���[�V�����f�[�^�擾
	aiAnimation* toanimation = m_ToAnimation;

	// �{�[���������[�v���ă{�[���s����쐬
	for (unsigned int c = 0; c < toanimation->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim = toanimation->mChannels[c];

		// �m�[�h������{�[���������g����assimp�̃{�[�������擾
		BONE* bone = &(m_BoneDictionary[nodeAnim->mNodeName.C_Str()]);

		int f;

		f = toframe % nodeAnim->mNumRotationKeys;				//�ȈՎ���
		aiQuaternion rot = nodeAnim->mRotationKeys[f].mValue;

		f = toframe % nodeAnim->mNumPositionKeys;				//�ȈՎ���
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

	// �u�����h����
	// �{�[���������[�v���ă{�[���s����쐬
	for (unsigned int c = 0; c < toanimation->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim = toanimation->mChannels[c];

		// �m�[�h������{�[���������g����assimp�̃{�[�������擾
		BONE* bone = &(m_BoneDictionary[nodeAnim->mNodeName.C_Str()]);

		Quaternion r = Quaternion::Slerp(bone->fromQuat, bone->toQuat, blendarate);
		Vector3 t = Vector3::Lerp(bone->fromPos, bone->toPos, blendarate);
		Vector3 s = Vector3::Lerp(bone->fromScale, bone->toScale, blendarate);

		Matrix scalemtx = Matrix::CreateScale(s.x, s.y, s.z);
		Matrix rotmtx = Matrix::CreateFromQuaternion(r);
		Matrix transmtx = Matrix::CreateTranslation(t.x, t.y, t.z);

		bone->AnimationMatrix = scalemtx * rotmtx * transmtx;
	}

	// �{�[���R���r�l�[�V�����s������ׂčċA���g�p���čX�V����
	UpdateBoneMatrix(&m_AssimpNodeNameTree, Matrix::Identity);

	// �{�[���R���r�l�[�V�����s��̔z����Z�b�g
	for (const auto& bone : m_BoneDictionary)
	{
		bonecombarray.ConstantBufferMemory.BoneCombMtx[bone.second.idx] = bone.second.Matrix.Transpose();
	}
}


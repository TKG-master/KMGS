#pragma once

#include "CStaticMesh.h"
#include "AssimpPerse.h"
#include "CTreeNode.h"	
#include "renderer.h"
#include "BoneCombMatrix.h"
#include "CStaticMeshRenderer.h"

class CAnimationMesh : public CStaticMesh
{
	// �{�[������
	std::unordered_map<std::string, BONE> m_BoneDictionary{};	// 20240714 DX��

	// �J�����g�̃A�j���[�V�����f�[�^
	aiAnimation* m_CurrentAnimation{};

	aiAnimation* m_FromAnimation{};
	aiAnimation* m_ToAnimation{};

	// assimp �m�[�h���c���[�i�e�q�֌W���킩��j
	CTreeNode<std::string>	m_AssimpNodeNameTree{};

	// �����_��
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

	// �K�w�\�����l�������{�[���R���r�l�[�V�����s����X�V
	void UpdateBoneMatrix(CTreeNode<std::string>* ptree, DirectX::SimpleMath::Matrix matrix);		// 20240714 DX��	

	// �A�j���[�V�����̍X�V
	void Update(BoneCombMatrix& bonecombarray, int& CurrentFrame);

	// �A�j���[�V�����̍X�V�i���[�V�����u�����h�j
	void BlendUpdate(
		BoneCombMatrix& bonecombarray,			// �{�[���R���r�l�[�V�����s��ƌ��݂̃t���[��	
		int fromframe, 							// FROM���̃��[�V�������ƃt���[��
		int toframe,							// TO���̃��[�V�������ƃt���[��
		float blendarate);						// ����

	// �`��
	void Draw();
};

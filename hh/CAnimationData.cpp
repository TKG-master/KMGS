#include	<cassert>
#include	<iostream>
#include	"CAnimationData.h"

const aiScene* CAnimationData::LoadAnimation(const std::string filename, const std::string name)
{
	// �V�[�������\�z
	m_Animation[name] = m_importer.ReadFile(
		filename.c_str(),
		aiProcess_ConvertToLeftHanded);
	assert(m_Animation[name]);

	if (m_Animation[name] == nullptr) {
		std::cout << " animation load error " << filename << " " << m_importer.GetErrorString();
	}

	return m_Animation[name];
}

// �w�肵�����O�̃A�j���[�V�����f�[�^���擾����
aiAnimation* CAnimationData::GetAnimation(const std::string name, int idx) {

	aiAnimation* animation = m_Animation[name]->mAnimations[idx];

	return animation;
}

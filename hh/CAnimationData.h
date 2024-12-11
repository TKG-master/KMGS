#pragma once
#include	<assimp\Importer.hpp>
#include	<assimp\scene.h>
#include	<assimp\postprocess.h>
#include	<assimp/cimport.h>
#include	<unordered_map>
#include	"NonCopyable.h"

class CAnimationData : NonCopyable {
	// ���̃A�j���[�V�����̃p�X��
	std::string m_filename;

	// �A�j���[�V�����f�[�^�i�[�����i�L�[�̓��[�V�������j
	std::unordered_map<std::string, const aiScene*> m_Animation;

	// importer����������ہ@�V�[������������̂Ń����o�ϐ��ɂ��Ă�
	Assimp::Importer m_importer;
public:
	// �A�j���[�V�����f�[�^�ǂݍ���
	const aiScene* LoadAnimation(const std::string filename, const std::string name);

	// �w�肵�����O�̃A�j���[�V�������擾����
	aiAnimation* GetAnimation(const std::string name, int idx = 0);

	// �A�j���[�V�����f�[�^���i�[����Ă��邁���r�����������l������
	const aiScene* GetAiScene(std::string name)
	{
		return m_Animation[name];
	}
};
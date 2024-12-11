#include "TerrainLoder.h"
#include <fstream>
#include <sstream>

// CTerrainLoader�N���X��static�����o�ϐ��̏�����
TerrainLoder* TerrainLoder::instance = nullptr;


TerrainLoder::TerrainLoder()
{
	// �t�@�C���̐��������[�v
	for (int i = 0; i < file_name.size(); i++)
	{
		// �p�X�����������Apath�z��Ɋi�[
		path.push_back(file_name[i].insert(0, "assets/Stage/"));
	}

	// �t�@�C���̐��������[�v
	for (int i = 0; i < Wandering_name.size(); i++)
	{
		// �p�X�����������Apath�z��Ɋi�[
		Wandering_path.push_back(Wandering_name[i].insert(0, "assets/Wandering/"));
	}

}

TerrainLoder::~TerrainLoder()
{

}

void TerrainLoder::CleanupSingleton()
{
	//�C���X�^���X������Ȃ�������
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

TerrainLoder* TerrainLoder::GetInstance()
{
	// �V���O���g�������݂��Ă��Ȃ��Ȃ琶������
	if (!instance)
	{
		// �V���O���g���̐���
		instance = new TerrainLoder();
		//�R�[���o�b�N�Ƃ��ēo�^
		std::atexit(CleanupSingleton);
	}
	//�B��̃C���X�^���X��Ԃ�
	return instance;
}

void TerrainLoder::LoadTerrainData(TERRAIN_ID stage)
{
	// �O�ɓǂݍ��܂ꂽ�����N���A����
	map_info.clear();

	// �ǂݍ��񂾃f�[�^���i�[

	std::string line;

	// �w�肳�ꂽcsv�t�@�C�����J��
	std::ifstream ifs_csv_file(path[(int)stage]);

	// �t�@�C��������ɊJ���Ă��邩�`�F�b�N
	if (!ifs_csv_file.is_open())
	{
		int a = 0;
		return;
	}

	// �f�[�^��ǂݍ���
	while (getline(ifs_csv_file, line))
	{
		std::vector<int> num;
		std::stringstream linestream(line);
		std::string cell;
		// �s�� ','�������܂ŌJ��Ԃ�
		while(getline(linestream, cell, ','))
		{
			try {
				int nu = std::stoi(cell);
				num.push_back(nu);
			}
			catch (const std::invalid_argument)
			{

			}
		}
		map_info.push_back(num);
	}
	// �t�@�C�������
	ifs_csv_file.close();
}

std::vector<std::vector<int>> TerrainLoder::GetTerrainData()
{
	return map_info;
}

void TerrainLoder::LoadWnderingData(TERRAIN_ID stage)
{
	// �O�ɓǂݍ��܂ꂽ�����N���A����
	Wandering_info.clear();

	// �ǂݍ��񂾃f�[�^���i�[

	std::string line;

	// �w�肳�ꂽcsv�t�@�C�����J��
	std::ifstream ifs_csv_file(Wandering_path[(int)stage]);

	// �t�@�C��������ɊJ���Ă��邩�`�F�b�N
	if (!ifs_csv_file.is_open())
	{
		int a = 0;
		return;
	}

	// �f�[�^��ǂݍ���
	while (getline(ifs_csv_file, line))
	{
		std::vector<int> num;
		std::stringstream linestream(line);
		std::string cell;
		// �s�� ','�������܂ŌJ��Ԃ�
		while (getline(linestream, cell, ','))
		{
			try {
				int nu = std::stoi(cell);
				num.push_back(nu);
			}
			catch (const std::invalid_argument)
			{
				//����int�^�ɕϊ��ł��Ȃ��������ɒʂ�
				int a = 0;
			}
		}
		Wandering_info.push_back(num);
	}

	// �t�@�C�������
	ifs_csv_file.close();
}

std::vector<std::vector<int>> TerrainLoder::GetWnderingData()
{
	return Wandering_info;
}



#pragma once
#include <vector>
#include <string>

// �}�b�v���\������{�b�N�X�̃T�C�Y
#define SIZEX		(60.0f)
//�������{�b�N�XY
#define SIZEY		(60.0f)
//�傫���{�b�N�XY
#define BIGSIZEY	(100.0f);

#define SIZEZ		(60.0f)

//�S�[���̃T�C�Y
#define GSIZEX		(25.0f)
#define GSIZEY		(25.0f)
#define GSIZEZ		(25.0f)

//���_���J�n�Ƃ���
#define ORIGIN_TILE_POS_X	(0.0f)
#define ORIGIN_TILE_POS_Z	(0.0f)

// �n�`�f�[�^�̎��ʎq
enum class TERRAIN_ID
{
	STAGE_TEST,
	STAGE_1,
	STAGE_2,
};


class TerrainLoder
{
private:

	// �B��̃C���X�^���X���i�[���邽�߂̃|�C���^
	static TerrainLoder* instance;
	// �X�e�[�W�f�[�^�̃t�@�C����
	std::vector<std::string> file_name =
	{
		"stage_Test.csv",
		"stageF_data.csv",
		"StageS_data.csv",
	};
	//���񃋁[�g�̃f�[�^
	std::vector<std::string> Wandering_name =
	{
		"Stage_T.csv",
		"Stage_Fw.csv",
		"Stage_Sw.csv"
	};
	//�G�̃p�����[�^�[�̃f�[�^
	std::vector<std::string> Eparameter_name =
	{
		"Stage_Tpara.csv",
		"Stage_Fpara.csv",
		"Stage_Spara.csv",
	};

	// ������A���Ŋ����������p�X�̏����i�[
	std::vector<std::string> path;
	// �}�b�v�f�[�^�ۑ��p
	std::vector<std::vector<int>> map_info;
	// ������A���Ŋ����������p�X�̏����i�[
	std::vector<std::string> Wandering_path;
	// �}�b�v�f�[�^�ۑ��p
	std::vector<std::vector<int>> Wandering_info;
	//�G�̃p�����[�^�[�̃f�[�^
	std::vector<std::vector<int>> Eparameter;
	std::vector<std::string> Eparameter_path;



	// �R���X�g���N�^
	TerrainLoder();
	// �f�X�g���N�^
	~TerrainLoder();
	// �A�v���P�[�V�����I�����ɃR�[���o�b�N�Ƃ��ČĂяo��(�V���O���g���̉��)
	static void CleanupSingleton();
public:

	// �C���X�^���X���擾���邽�߂̃��\�b�h
	static TerrainLoder* GetInstance();
	// �n�`�f�[�^�̓ǂݍ���
	void LoadTerrainData(TERRAIN_ID stage);
	// �n�`�f�[�^�̎擾���s��
	std::vector<std::vector<int>> GetTerrainData();

	void LoadWnderingData(TERRAIN_ID stage);

	void LoadEparameterData(TERRAIN_ID stage);

	std::vector<std::vector<int>> GetWnderingData();

	std::vector<std::vector<int>> GetEparameter();

};


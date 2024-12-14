#pragma once
#include "GUI.h"
#include "TerrainLoder.h"

class Enemy;

class BoxObj;

class GoalObj;

//�V�[���N���X�̌��� ���̃V�[����e�N���X�ɂ��ăV�[��������Ă���
class CScene
{
public:
	//�R���X�g���N�^
	CScene();
	//�f�X�X�g���^
	~CScene();

	//�I�[�o�[���C�h����p
	virtual void Init();

	virtual void Update();

	virtual void Draw();

	virtual void UnInit();

	void CreateStage(TERRAIN_ID ID);

	DirectX::SimpleMath::Vector3 GetPlayerStartPos() { return PlayerStartPos; };

	DirectX::SimpleMath::Vector3 GetGoalPos() { return GoalPos; };

	std::vector<DirectX::SimpleMath::Vector3> GetEnemyStartPoss() { return ENEMYS; };

	static std::vector<std::vector<int>> GetMapData() { return map_data; };

	DirectX::SimpleMath::Vector3 GetCameraPos() { return CameraPos; };

	static std::vector<std::vector<int>> GetWanderingdata() { return Wandering_data; };


	DirectX::SimpleMath::Vector3 GetStartEasingPlayerPos() {
		StartEasingPlayerPos = PlayerStartPos;
		StartEasingPlayerPos.y += 500.0f;
		return StartEasingPlayerPos;
	}

	//�{�b�N�X�̔z��
	static std::vector<BoxObj*> BOXS;

	static BoxObj* floorBox;

protected:

	//�G�̔z��
	std::vector<DirectX::SimpleMath::Vector3> ENEMYS;
	// �}�b�v�f�[�^�Ɋ֘A����ϐ��Q
	static std::vector<std::vector<int>> map_data;
	//�G�̜p�j���[�g�Ɋ֘A����f�[�^
	static std::vector<std::vector<int>> Wandering_data;

	DirectX::SimpleMath::Vector3 PlayerStartPos;
	DirectX::SimpleMath::Vector3 StartEasingPlayerPos;
	DirectX::SimpleMath::Vector3 GoalPos;
	DirectX::SimpleMath::Vector3 CameraPos;


	// �e�^�C���̃T�C�Y
	const float tile_size_x = SIZEX;
	const float tile_size_y = SIZEY;
	const float Bigtile_size_y = BIGSIZEY;
	const float tile_size_z = SIZEZ;

	float x_tile = ORIGIN_TILE_POS_X;
	float z_tile = ORIGIN_TILE_POS_Z;

	float total_width = 0.0f;
	float total_depth = 0.0f;

};


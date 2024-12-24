#pragma once
#include "CScene.h"
#include "Camera.h"
#include "Field.h"
#include "Player.h"
#include "Enemy.h"
#include "Radar.h"
#include "structs.h"
#include "BoxObj.h"
#include "GoalObj.h"
#include "Timer.h"
#include "EnemyManager.h"
#include "GameManager.h"
#include "SkyDome.h"
#include "GameResult.h"
#include "DirectWrite.h"




//�F�X�����V�[��
class CTest : public CScene
{
private:
	DirectX::SimpleMath::Vector3 CharacterScale = DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f);

	Radar* radar;
	Camera* camera;
	Field field;
	Player* Pl;
	EnemyManager* EM;
	Timer* gameTime;
	GameManager* GM;
	GoalObj* goal;
	SkyDome* Dome;
	DirectWrite* Write;

	GameUI* GoalUI;
	GameUI* SpaceUI;
	GameUI* ClearUI;
	GameUI* KeyUI;
	GameUI* failedUI;
	GameUI* WalkUI;

	GameUI* Fade;
	bool FadeOut = false;

	//�C�[�W���O���Ă��Ȃ���
	bool isEasing = true;
	//�C�[�W���O������
	bool isEasingStart = true;

public:

	float CamZoomSpeed = 1.0f;

	//�R���X�g���N�^
	CTest();
	//�f�X�X�g���N�^
	~CTest();

	//�֐��̃I�[�o�[���C�h
	void Update() override;
	void Draw() override;
	void Init() override;
	void UnInit() override;
};


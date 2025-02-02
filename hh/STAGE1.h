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
#include "EasingController.h"
#include "SkyDome.h"
#include "GameUI.h"
#include "TimerUI.h"
#include "Polygon2D.h"
#include "DirectWrite.h"
#include "Book.h"
#include "UIManager.h"
#include "Uragiri.h"


class STAGE1 : public CScene
{
private:
	DirectX::SimpleMath::Vector3 StartPlayerPos = DirectX::SimpleMath::Vector3(-200.0f, 0.0f, -200.0f);
	DirectX::SimpleMath::Vector3 CharacterScale = DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f);

	Radar* radar;

	Camera* camera;
	Camera* Scamera;
	Field field;
	Player* Pl;
	EnemyManager* EM;
	Timer* gameTime;
	EasingController* GM;
	GoalObj* goal;
	SkyDome* Dome;
	Uragiri* uragiri;

	GameUI* GoalUI;
	GameUI* ClearUI;
	GameUI* failedUI;
	GameUI* StartUI;
	GameUI* PushUI;
	GameUI* explainUI;
	UIManager* UM;

	GameUI* Fade;
	bool FadeOut = false;

	//�C�[�W���O���Ă��Ȃ���
	bool isEasing = true;
	//�C�[�W���O������
	bool isEasingStart = true;

	bool SUI = true;

public:

	float CamZoomSpeed = 1.0f;

	//�R���X�g���N�^
	STAGE1();
	//�f�X�X�g���N�^
	~STAGE1();

	//�֐��̃I�[�o�[���C�h
	void Update() override;
	void Draw() override;
	void Init() override;
	void UnInit() override;
};


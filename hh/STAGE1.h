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
#include "TimerUI.h"
#include "Polygon2D.h"
#include "DirectWrite.h"


class STAGE1 : public CScene
{
private:
	DirectX::SimpleMath::Vector3 StartPlayerPos = DirectX::SimpleMath::Vector3(-200.0f, 0.0f, -200.0f);
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
	DirectWrite* StartWrite;

	GameUI* GoalUI;
	GameUI* SpaceUI;
	GameUI* ClearUI;
	GameUI* KeyUI;
	GameUI* failedUI;
	GameUI* WalkUI;
	GameUI* StartUI;

	GameUI* Fade;
	bool FadeOut = false;

	//イージングしていない時
	bool isEasing = true;
	//イージングした後
	bool isEasingStart = true;

	bool SUI = true;

public:

	float CamZoomSpeed = 1.0f;

	//コンストラクタ
	STAGE1();
	//デスストラクタ
	~STAGE1();

	//関数のオーバーライド
	void Update() override;
	void Draw() override;
	void Init() override;
	void UnInit() override;
};


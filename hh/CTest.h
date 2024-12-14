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




//色々試すシーン
class CTest : public CScene
{
private:
	DirectX::SimpleMath::Vector3 CharacterScale = DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f);

	Radar* radar;
	Camera* camera;
	Field field;
	CCollision collision;
	Player* Pl;
	EnemyManager* EM;
	Timer* gameTime;
	GameManager* GM;
	GoalObj* goal;
	SkyDome* Dome;
	GameUI* GoalUI;
	GameUI* SpaceUI;
	GameUI* ClearUI;
	GameUI* failedUI;

	//イージングしていない時
	bool isEasing = true;
	//イージングした後
	bool isEasingStart = true;

public:

	float CamZoomSpeed = 1.0f;

	//コンストラクタ
	CTest();
	//デスストラクタ
	~CTest();

	//関数のオーバーライド
	void Update() override;
	void Draw() override;
	void Init() override;
	void UnInit() override;
};


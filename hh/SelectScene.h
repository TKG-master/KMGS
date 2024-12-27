#pragma once
#include "CScene.h"
#include "Camera.h"
#include "GoalObj.h"
#include "Player.h"
#include "SkyDome.h"
#include "GameResult.h"
#include "GameManager.h"


class SelectScene : public CScene
{
private:
	GoalObj* goal;
	Camera* Cam;
	SkyDome* Dome;


	GameUI* SELECT;
	GameUI* STAGE1;
	GameUI* STAGE2;
	GameUI* STAGE3;
	GameUI* UISelect;

	GameManager* GM;
	GameUI* Fade;
	bool FadeOut = false;


public:
	SelectScene();
	~SelectScene();


	//関数のオーバーライド
	void Update() override;
	void Draw() override;
	void Init() override;
	void UnInit() override;
};


#pragma once
#include "CScene.h"
#include "Camera.h"
#include "GoalObj.h"
#include "Player.h"
#include "SkyDome.h"
#include "GameUI.h"
#include "EasingController.h"


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
	GameUI* StageImage;
	GameUI* StageImage2;
	GameUI* StageImage3;
	GameUI* UISelect;

	EasingController* GM;
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


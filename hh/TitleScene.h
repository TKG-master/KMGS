#pragma once
#include "CScene.h"
#include "Camera.h"
#include "GoalObj.h"
#include "Player.h"
#include "SkyDome.h"
#include "GameUI.h"
#include "EasingController.h"
#include "DirectWrite.h"
#include "Timer.h"
#include "xa2.h"

class TitleScene : public CScene
{
private:
	GoalObj* goal;
	Camera* Cam;
	SkyDome* Dome;
	GameUI* GR;
	GameUI* UI2;
	GameUI* Fade;
	EasingController* GM;


	bool FadeOut = false;

public:
	TitleScene();
	~TitleScene();


	//関数のオーバーライド
	void Update() override;
	void Draw() override;
	void Init() override;
	void UnInit() override;

};


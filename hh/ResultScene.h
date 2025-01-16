#pragma once
#include "CScene.h"
#include "Camera.h"
#include "GoalObj.h"
#include "Player.h"
#include "SkyDome.h"
#include "GameUI.h"
#include "EasingController.h"
#include "Xa2.h"

class ResultScene : public CScene
{
private:
	GoalObj* goal;
	Camera* Cam;
	SkyDome* Dome;

	GameUI* Result;
	GameUI* BsckTitle;
	GameUI* Select;
	GameUI* UISelect;

	EasingController* GM;
	GameUI* Fade;
	bool FadeOut = false;

public:
	ResultScene();
	~ResultScene();


	//関数のオーバーライド
	void Update() override;
	void Draw() override;
	void Init() override;
	void UnInit() override;

};


#pragma once
#include "CScene.h"
#include "Camera.h"
#include "GoalObj.h"
#include "Player.h"
#include "SkyDome.h"
#include "GameResult.h"
#include "GameManager.h"

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

	GameManager* GM;
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


#pragma once
#include "CScene.h"
#include "Camera.h"
#include "GoalObj.h"
#include "Player.h"
#include "SkyDome.h"
#include "GameResult.h"

class ResultScene : public CScene
{
private:
	GoalObj* goal;
	Camera* Cam;
	SkyDome* Dome;

	GameUI* GR;
	GameUI* UI2;
	GameUI* UI3;
	GameUI* UISelect;

public:
	ResultScene();
	~ResultScene();


	//関数のオーバーライド
	void Update() override;
	void Draw() override;
	void Init() override;
	void UnInit() override;

};


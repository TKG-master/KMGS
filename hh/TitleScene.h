#pragma once
#include "CScene.h"
#include "Camera.h"
#include "GoalObj.h"
#include "Player.h"
#include "SkyDome.h"
#include "GameResult.h"
#include "GameManager.h"



class TitleScene : public CScene
{
private:
	GoalObj* goal;
	Camera* Cam;
	SkyDome* Dome;
	GameUI* GR;
	GameUI* UI2;
	GameUI* Fade;
	GameManager* GM;
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


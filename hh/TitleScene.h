#pragma once
#include "CScene.h"
#include "Camera.h"
#include "GoalObj.h"
#include "Player.h"
#include "SkyDome.h"
#include "GameResult.h"



class TitleScene : public CScene
{
private:
	Player* Pl;
	GoalObj* goal;
	Camera* Cam;
	SkyDome* Dome;
	GameUI* GR;

public:
	TitleScene();
	~TitleScene();


	//関数のオーバーライド
	void Update() override;
	void Draw() override;
	void Init() override;
	void UnInit() override;

};


#pragma once
#include "CScene.h"
#include "Camera.h"
#include "GoalObj.h"
#include "Player.h"
#include "SkyDome.h"



class TitleScene : public CScene
{
private:
	Player* Pl;
	GoalObj* goal;
	Camera* Cam;
	SkyDome* Dome;

public:
	TitleScene();
	~TitleScene();


	//�֐��̃I�[�o�[���C�h
	void Update() override;
	void Draw() override;
	void Init() override;
	void UnInit() override;

};


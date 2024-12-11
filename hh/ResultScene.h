#pragma once
#include "CScene.h"
#include "Camera.h"

class ResultScene : public CScene
{
private:
	Camera* Cam;

public:
	ResultScene();
	~ResultScene();


	//�֐��̃I�[�o�[���C�h
	void Update() override;
	void Draw() override;
	void Init() override;
	void UnInit() override;

};


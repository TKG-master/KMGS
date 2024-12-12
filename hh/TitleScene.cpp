#include "TitleScene.h"
#include "CSceneManager.h"
#include "Input.h"

TitleScene::TitleScene()
{
	goal = new GoalObj(100.0f, 100.0f, 100.0f);
	goal->SetPosition(Vector3(0.0f,0.0f,0.0f));

	Cam = new Camera(Vector3(0.0f,200.0f,0.0f));
	Cam->SetFoucus(Vector3(0.0f, 0.0f, 0.0f));

	Dome = new SkyDome();
	Dome->DrawInit(2000.0f, "assets\\MGfloor.jpeg");

	GR = new GameUI();
	GR->Init("assets\\START.png");

}

TitleScene::~TitleScene()
{

}

void TitleScene::Update()
{
	Dome->Update();

	goal->TitleUpdate();

	Cam->LateUpdate(goal->GetPosition(), 0.5f);

	if (Input::Get()->GetKeyPress(DIK_SPACE))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_1);
	}

}

void TitleScene::Draw()
{

	Dome->Draw();

	goal->Draw();

	GR->Draw();

	Cam->Draw();

}

void TitleScene::Init()
{

}

void TitleScene::UnInit()
{

	delete goal;
	goal = nullptr;

	delete Cam;
	Cam = nullptr;

	delete Dome;
	Dome = nullptr;

	delete GR;
	GR = nullptr;
}

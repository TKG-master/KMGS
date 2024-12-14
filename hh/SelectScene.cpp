#include "SelectScene.h"
#include "CSceneManager.h"
#include "Input.h"

SelectScene::SelectScene()
{
	goal = new GoalObj(100.0f, 100.0f, 100.0f);
	goal->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

	Cam = new Camera(Vector3(0.0f, 200.0f, 0.0f));
	Cam->SetFoucus(Vector3(0.0f, 0.0f, 0.0f));

	Dome = new SkyDome();
	Dome->DrawInit(2000.0f, "assets\\MGfloor.jpeg");

	GR = new GameUI();
	GR->Init("assets\\SelectUI.png");
	GR->SetCenter(Vector2(200.0f, 80.0f));
	GR->SetHeight(200.0f);
	GR->SetWidth(500.0f);

	UI2 = new GameUI();
	UI2->Init("assets\\STAGE1UI.png");
	UI2->SetCenter(Vector2(400.0f, 500.0f));
	UI2->SetHeight(100.0f);
	UI2->SetWidth(300.0f);

	UI3 = new GameUI();
	UI3->Init("assets\\STAGE2UI.png");
	UI3->SetCenter(Vector2(900.0f, 500.0f));
	UI3->SetHeight(100.0f);
	UI3->SetWidth(300.0f);


	UISelect = new GameUI();
	UISelect->Init("assets\\siro.jpg");
	UISelect->SetCenter(Vector2(400.0f, 500.0f));
	UISelect->SetHeight(100.0f);
	UISelect->SetWidth(300.0f);
	UISelect->SetColor(Color(0, 0.5, 0.5, 0.5f));
}

SelectScene::~SelectScene()
{

}

void SelectScene::Update()
{
	Dome->Update();


	goal->TitleUpdate();



	Cam->LateUpdate(goal->GetPosition(), 0.5f);

	if (Input::Get()->GetKeyTrigger(DIK_RIGHT) && UISelect->GetCenter() != UI3->GetCenter())
	{
		UISelect->SetCenter(UI3->GetCenter());
	}
	else if (Input::Get()->GetKeyTrigger(DIK_LEFT) && UISelect->GetCenter() != UI2->GetCenter())
	{
		UISelect->SetCenter(UI2->GetCenter());
	}

	if (Input::Get()->GetKeyTrigger(DIK_SPACE))
	{
		if (UISelect->GetCenter() == UI2->GetCenter())
		{
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_1);
		}
		else if (UISelect->GetCenter() == UI3->GetCenter())
		{
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TEST);
		}
	}

}

void SelectScene::Draw()
{
	Dome->Draw();

	goal->Draw();

	GR->Draw();

	UI2->Draw();

	UI3->Draw();

	UISelect->Draw();

	Cam->Draw();
}

void SelectScene::Init()
{
}

void SelectScene::UnInit()
{
	delete goal;
	goal = nullptr;

	delete Cam;
	Cam = nullptr;

	delete Dome;
	Dome = nullptr;

	delete GR;
	GR = nullptr;

	delete UI2;
	UI2 = nullptr;

	delete UI3;
	UI3 = nullptr;

	delete UISelect;
	UISelect = nullptr;
}

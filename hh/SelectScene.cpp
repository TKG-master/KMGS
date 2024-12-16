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

	SELECT = new GameUI();
	SELECT->Init("assets\\SelectUI.png");
	SELECT->SetCenter(Vector2(200.0f, 80.0f));
	SELECT->SetHeight(200.0f);
	SELECT->SetWidth(500.0f);

	STAGE1 = new GameUI();
	STAGE1->Init("assets\\STAGE1UI.png");
	STAGE1->SetCenter(Vector2(400.0f, 500.0f));
	STAGE1->SetHeight(100.0f);
	STAGE1->SetWidth(300.0f);

	STAGE2 = new GameUI();
	STAGE2->Init("assets\\STAGE2UI.png");
	STAGE2->SetCenter(Vector2(900.0f, 500.0f));
	STAGE2->SetHeight(100.0f);
	STAGE2->SetWidth(300.0f);


	UISelect = new GameUI();
	UISelect->Init("assets\\siro.jpg");
	UISelect->SetCenter(Vector2(400.0f, 500.0f));
	UISelect->SetHeight(100.0f);
	UISelect->SetWidth(300.0f);
	UISelect->SetColor(Color(0, 0.5, 0.5, 0.5f));

	Fade = new GameUI();
	Fade->Init("assets\\siro.jpg");
	Fade->SetCenter(Vector2(960.0f, 540.0f));
	Fade->SetHeight(1080.0f);
	Fade->SetWidth(1920.0f);
	Fade->SetColor(Color(0.0, 0.0, 0.0, 1.0f));

	GM = new GameManager();

	Input::Get()->Setkeyflg(false);

}

SelectScene::~SelectScene()
{

}

void SelectScene::Update()
{
	GM->FadeIn(Fade);
	if (!GM->GetFadein())
	{
		Input::Get()->Setkeyflg(true);
	}

	Dome->Update();

	goal->TitleUpdate();

	Cam->LateUpdate(goal->GetPosition(), 0.5f ,0.0f);

	//ƒJ[ƒ\ƒ‹‚ÌˆÚ“®
	if (Input::Get()->GetKeyTrigger(DIK_RIGHT) && UISelect->GetCenter() != STAGE2->GetCenter())
	{
		UISelect->SetCenter(STAGE2->GetCenter());
	}
	else if (Input::Get()->GetKeyTrigger(DIK_LEFT) && UISelect->GetCenter() != STAGE1->GetCenter())
	{
		UISelect->SetCenter(STAGE1->GetCenter());
	}




	if (Input::Get()->GetKeyTrigger(DIK_SPACE))
	{
		this->FadeOut = true;
	}

	if (this->FadeOut)
	{

		GM->FadeOut(Fade);
		if (UISelect->GetCenter() == STAGE1->GetCenter() && !GM->GetFadeout())
		{
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_1);
		}
		else if (UISelect->GetCenter() == STAGE2->GetCenter() && !GM->GetFadeout())
		{
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TEST);
		}
	}
}

void SelectScene::Draw()
{
	Dome->Draw();

	goal->Draw();

	SELECT->Draw();

	STAGE1->Draw();

	STAGE2->Draw();

	UISelect->Draw();

	Fade->Draw();

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

	delete SELECT;
	SELECT = nullptr;

	delete STAGE1;
	STAGE1 = nullptr;

	delete STAGE2;
	STAGE2 = nullptr;

	delete UISelect;
	UISelect = nullptr;

	delete Fade;
	Fade = nullptr;

	delete GM;
	GM = nullptr;
}

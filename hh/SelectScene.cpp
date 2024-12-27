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
	Dome->DrawInit(2000.0f, "assets\\Texture\\MGfloor.jpeg");

	SELECT = new GameUI();
	SELECT->Init("assets\\Texture\\SelectUI.png");
	SELECT->SetCenter(Vector2(200.0f, 80.0f));
	SELECT->SetHeight(200.0f);
	SELECT->SetWidth(500.0f);

	STAGE1 = new GameUI();
	STAGE1->Init("assets\\Texture\\STAGE1UI.png");
	STAGE1->SetCenter(Vector2(1400.0f, 200.0f));
	STAGE1->SetHeight(150.0f);
	STAGE1->SetWidth(300.0f);

	STAGE2 = new GameUI();
	STAGE2->Init("assets\\Texture\\STAGE2UI.png");
	STAGE2->SetCenter(Vector2(1400.0f, 400.0f));
	STAGE2->SetHeight(150.0f);
	STAGE2->SetWidth(300.0f);

	STAGE3 = new GameUI();
	STAGE3->Init("assets\\Texture\\STERT3UI.png");
	STAGE3->SetCenter(Vector2(1400.0f, 600.0f));
	STAGE3->SetHeight(150.0f);
	STAGE3->SetWidth(300.0f);


	UISelect = new GameUI();
	UISelect->Init("assets\\Texture\\siro.jpg");
	UISelect->SetCenter(Vector2(1200.0f, 200.0f));
	UISelect->SetHeight(100.0f);
	UISelect->SetWidth(100.0f);
	UISelect->SetColor(Color(0.0, 0.5, 0.5, 0.5f));

	Fade = new GameUI();
	Fade->Init("assets\\Texture\\siro.jpg");
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

	Cam->FocusCamera(goal->GetPosition(), 0.5f ,0.0f);

	//カーソルの移動
	if (Input::Get()->GetKeyTrigger(DIK_S) && UISelect->GetCenter().y == STAGE1->GetCenter().y)
	{
		UISelect->SetCenter(Vector2(STAGE2->GetCenter().x - 200 ,STAGE2->GetCenter().y));
	}
	else if (Input::Get()->GetKeyTrigger(DIK_S) && UISelect->GetCenter().y == STAGE2->GetCenter().y)
	{
		UISelect->SetCenter(Vector2(STAGE3->GetCenter().x - 200 ,STAGE3->GetCenter().y));
	}
	else if (Input::Get()->GetKeyTrigger(DIK_W) && UISelect->GetCenter().y == STAGE3->GetCenter().y)
	{
		UISelect->SetCenter(Vector2(STAGE2->GetCenter().x - 200, STAGE2->GetCenter().y));
	}
	else if (Input::Get()->GetKeyTrigger(DIK_W) && UISelect->GetCenter().y == STAGE2->GetCenter().y)
	{
		UISelect->SetCenter(Vector2(STAGE1->GetCenter().x - 200, STAGE1->GetCenter().y));
	}




	if (Input::Get()->GetKeyTrigger(DIK_SPACE))
	{
		this->FadeOut = true;
	}

	//フェードしてシーンの移動
	if (this->FadeOut)
	{
		GM->FadeOut(Fade);
		if (UISelect->GetCenter().y == STAGE1->GetCenter().y && !GM->GetFadeout())
		{
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_1);
		}
		else if (UISelect->GetCenter().y == STAGE2->GetCenter().y && !GM->GetFadeout())
		{
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TEST);
		}
		else if (UISelect->GetCenter().y == STAGE3->GetCenter().y && !GM->GetFadeout())
		{
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_2);
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

	STAGE3->Draw();

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

	delete STAGE3;
	STAGE3 = nullptr;

	delete UISelect;
	UISelect = nullptr;

	delete Fade;
	Fade = nullptr;

	delete GM;
	GM = nullptr;
}

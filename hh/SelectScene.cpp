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
	SELECT->Init("assets\\Texture\\Select.png");
	SELECT->SetCenter(Vector2(200.0f, 80.0f));
	SELECT->SetHeight(200.0f);
	SELECT->SetWidth(500.0f);
	SELECT->SetColor(Color(0.5f, 0.5f, 0.5f, 1.0f));

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
	UISelect->Init("assets\\Texture\\SelectUI.png");
	UISelect->SetCenter(Vector2(1200.0f, 200.0f));
	UISelect->SetHeight(100.0f);
	UISelect->SetWidth(100.0f);
	UISelect->SetColor(Color(1.0, 1.0, 1.0, 0.7f));

	Fade = new GameUI();
	Fade->Init("assets\\Texture\\siro.jpg");
	Fade->SetCenter(Vector2(960.0f, 540.0f));
	Fade->SetHeight(1080.0f);
	Fade->SetWidth(1920.0f);
	Fade->SetColor(Color(0.0, 0.0, 0.0, 1.0f));

	StageImage = new GameUI();
	StageImage->Init("assets\\Texture\\StageImage.png");
	StageImage->SetCenter(Vector2(500.0f, 540.0f));
	StageImage->SetHeight(0.0f);
	StageImage->SetWidth(0.0f);
	StageImage->SetColor(Color(1.0, 1.0, 1.0, 1.0f));

	StageImage2 = new GameUI();
	StageImage2->Init("assets\\Texture\\StageImage2.png");
	StageImage2->SetCenter(Vector2(500.0f, 540.0f));
	StageImage2->SetHeight(0.0f);
	StageImage2->SetWidth(0.0f);
	StageImage2->SetColor(Color(1.0, 1.0, 1.0, 1.0f));

	StageImage3 = new GameUI();
	StageImage3->Init("assets\\Texture\\StageImage3.png");
	StageImage3->SetCenter(Vector2(500.0f, 540.0f));
	StageImage3->SetHeight(0.0f);
	StageImage3->SetWidth(0.0f);
	StageImage3->SetColor(Color(1.0, 1.0, 1.0, 1.0f));


	GM = new EasingController();

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
		GM->SetImageEasingEnd(true);
	}
	else if (Input::Get()->GetKeyTrigger(DIK_S) && UISelect->GetCenter().y == STAGE2->GetCenter().y)
	{
		UISelect->SetCenter(Vector2(STAGE3->GetCenter().x - 200 ,STAGE3->GetCenter().y));
		GM->SetImageEasingEnd(true);
	}
	else if (Input::Get()->GetKeyTrigger(DIK_W) && UISelect->GetCenter().y == STAGE3->GetCenter().y)
	{
		UISelect->SetCenter(Vector2(STAGE2->GetCenter().x - 200, STAGE2->GetCenter().y));
		GM->SetImageEasingEnd(true);
	}
	else if (Input::Get()->GetKeyTrigger(DIK_W) && UISelect->GetCenter().y == STAGE2->GetCenter().y)
	{
		UISelect->SetCenter(Vector2(STAGE1->GetCenter().x - 200, STAGE1->GetCenter().y));
		GM->SetImageEasingEnd(true);
	}

	if (UISelect->GetCenter().y == STAGE1->GetCenter().y)
	{

		GM->SelectEasing(STAGE1);
		STAGE2->SetWidth(300.0f);
		STAGE2->SetHeight(150.0f);
		STAGE3->SetWidth(300.0f);
		STAGE3->SetHeight(150.0f);

		//ステージの画像のイージング
		GM->ImageEasing(StageImage);
		StageImage2->SetWH(Vector3(0.0f, 0.0f, 0.0f));
		StageImage3->SetWH(Vector3(0.0f, 0.0f, 0.0f));
	}
	else if (UISelect->GetCenter().y == STAGE2->GetCenter().y)
	{

		GM->SelectEasing(STAGE2);
		STAGE1->SetWidth(300.0f);
		STAGE1->SetHeight(150.0f);
		STAGE3->SetWidth(300.0f);
		STAGE3->SetHeight(150.0f);

		//ステージの画像のイージング
		GM->ImageEasing(StageImage2);
		StageImage->SetWH(Vector3(0.0f, 0.0f, 0.0f));
		StageImage3->SetWH(Vector3(0.0f, 0.0f, 0.0f));

	}
	else if (UISelect->GetCenter().y == STAGE3->GetCenter().y)
	{

		GM->SelectEasing(STAGE3);
		STAGE1->SetWidth(300.0f);
		STAGE1->SetHeight(150.0f);
		STAGE2->SetWidth(300.0f);
		STAGE2->SetHeight(150.0f);

		//ステージの画像のイージング
		GM->ImageEasing(StageImage3);
		StageImage->SetWH(Vector3(0.0f, 0.0f, 0.0f));
		StageImage2->SetWH(Vector3(0.0f, 0.0f, 0.0f));
	}


	if (Input::Get()->GetKeyTrigger(DIK_SPACE))
	{
		this->FadeOut = true;
	}
	//フェードしてシーンの移動
	else if (this->FadeOut)
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

	StageImage->Draw();

	StageImage2->Draw();

	StageImage3->Draw();

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

	delete StageImage;
	StageImage = nullptr;

	delete StageImage2;
	StageImage2 = nullptr;

	delete StageImage3;
	StageImage2 = nullptr;

	delete Fade;
	Fade = nullptr;

	delete GM;
	GM = nullptr;
}

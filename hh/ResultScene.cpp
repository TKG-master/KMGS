#include "ResultScene.h"
#include "CSceneManager.h"
#include "Input.h"

ResultScene::ResultScene()
{
	goal = new GoalObj(100.0f, 100.0f, 100.0f);
	goal->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

	Cam = new Camera(Vector3(0.0f, 200.0f, 0.0f));
	Cam->SetFoucus(Vector3(0.0f, 0.0f, 0.0f));

	Dome = new SkyDome();
	Dome->DrawInit(2000.0f, "assets\\Texture\\MGfloor.jpeg");

	Result = new GameUI();
	Result->Init("assets\\Texture\\ResultUI.png");
	Result->SetCenter(Vector2(200.0f, 80.0f));
	Result->SetHeight(200.0f);
	Result->SetWidth(500.0f);

	BsckTitle = new GameUI();
	BsckTitle->Init("assets\\Texture\\BsckTitleUI.png");
	BsckTitle->SetCenter(Vector2(900.0f, 400.0f));
	BsckTitle->SetHeight(100.0f);
	BsckTitle->SetWidth(300.0f);

	Select = new GameUI();
	Select->Init("assets\\Texture\\Select.png");
	Select->SetCenter(Vector2(900.0f, 700.0f));
	Select->SetHeight(100.0f);
	Select->SetWidth(300.0f);


	UISelect = new GameUI();
	UISelect->Init("assets\\Texture\\SelectUI.png");
	UISelect->SetCenter(Vector2(BsckTitle->GetCenter().x - 200, BsckTitle->GetCenter().y));
	UISelect->SetHeight(100.0f);
	UISelect->SetWidth(100.0f);
	UISelect->SetColor(Color(1.0f, 1.0f, 1.0f, 0.7f));

	Fade = new GameUI();
	Fade->Init("assets\\Texture\\siro.jpg");
	Fade->SetCenter(Vector2(960.0f, 540.0f));
	Fade->SetHeight(1080.0f);
	Fade->SetWidth(1920.0f);
	Fade->SetColor(Color(0.0f, 0.0f, 0.0f, 1.0f));

	GM = new EasingController();

	Input::Get()->Setkeyflg(false);

}

ResultScene::~ResultScene()
{

}

void ResultScene::Update()
{
	GM->FadeIn(Fade);
	if (!GM->GetFadein())
	{
		Input::Get()->Setkeyflg(true);
	}

	Dome->Update();


	goal->TitleUpdate();



	Cam->FocusCamera(goal->GetPosition(), 0.5f,0.0f);

	//カーソルの移動
	if (Input::Get()->GetKeyTrigger(DIK_S) && UISelect->GetCenter() != Select->GetCenter())
	{
		XA_Play(SOUND_LABEL_SELECT);
		UISelect->SetCenter(Vector2(Select->GetCenter().x - 200.0f, Select->GetCenter().y));
	}
	//カーソルの移動
	else if (Input::Get()->GetKeyTrigger(DIK_W) && UISelect->GetCenter() != BsckTitle->GetCenter())
	{
		XA_Play(SOUND_LABEL_SELECT);
		UISelect->SetCenter(Vector2(BsckTitle->GetCenter().x - 200.0f, BsckTitle->GetCenter().y));
	}

	if (UISelect->GetCenter().y == Select->GetCenter().y)
	{

		GM->SelectEasing(Select);
		BsckTitle->SetWidth(300.0f);
		BsckTitle->SetHeight(150.0f);

	}
	else if (UISelect->GetCenter().y == BsckTitle->GetCenter().y)
	{

		GM->SelectEasing(BsckTitle);
		Select->SetWidth(300.0f);
		Select->SetHeight(150.0f);

	}





	//決定したとき
	if (Input::Get()->GetKeyTrigger(DIK_SPACE))
	{
		this->FadeOut = true;
		XA_Play(SOUND_LABEL_KETEI);
		Input::Get()->Setkeyflg(false);
	}
	if (this->FadeOut)
	{
		GM->FadeOut(Fade);
		if (UISelect->GetCenter().y == BsckTitle->GetCenter().y && !GM->GetFadeout())
		{
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
		}
		else if (UISelect->GetCenter().y == Select->GetCenter().y && !GM->GetFadeout())
		{
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT);
		}
	}

}

void ResultScene::Draw()
{
	Dome->Draw();

	goal->Draw();

	Result->Draw();

	BsckTitle->Draw();

	Select->Draw();

	UISelect->Draw();

	Fade->Draw();

	Cam->Draw();
}

void ResultScene::Init()
{

}

void ResultScene::UnInit()
{

	delete goal;
	goal = nullptr;

	delete Cam;
	Cam = nullptr;

	delete Dome;
	Dome = nullptr;

	delete Result;
	Result = nullptr;

	delete BsckTitle;
	BsckTitle = nullptr;

	delete Select;
	Select = nullptr;

	delete UISelect;
	UISelect = nullptr;

	delete Fade;
	Fade = nullptr;

	delete GM;
	GM = nullptr;

}

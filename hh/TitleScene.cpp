#include "TitleScene.h"
#include "CSceneManager.h"
#include "Input.h"

TitleScene::TitleScene()
{

	goal = new GoalObj(100.0f, 100.0f, 100.0f);
	goal->SetPosition(Vector3(0.0f,0.0f,0.0f));

	Cam = new Camera(Vector3(0.0f,200.0f,0.0f));
	Cam->SetFoucus(Vector3(0.0f, 0.0f, 0.0f));

	Book = new FBXMesh();
	Book->Init();
	Book->Setpos(Vector3(0.0f, 0.0f, 0.0f));
	Book->Setscale(Vector3(100.0f,100.0f, 100.0f));
	Book->Setrot(Vector3(90.0f, 0.0f, 0.0f));


	Dome = new SkyDome();
	Dome->DrawInit(2000.0f, "assets\\Texture\\MGfloor.jpeg");

	GR = new GameUI();
	GR->Init("assets\\Texture\\START.png");
	GR->SetCenter(Vector2(650.0f, 450.0f));

	UI2 = new GameUI();
	UI2->Init("assets\\Texture\\SPACEUI.png");
	UI2->SetCenter(Vector2(200.0f, 800.0f));
	UI2->SetHeight(200.0f);
	UI2->SetWidth(250.0f);



	Fade = new GameUI();
	Fade->Init("assets\\Texture\\siro.jpg");
	Fade->SetCenter(Vector2(960.0f, 540.0f));
	Fade->SetHeight(1080.0f);
	Fade->SetWidth(1920.0f);
	Fade->SetColor(Color(0.0, 0.0, 0.0, 1.0f));

	GM = new GameManager();

	Input::Get()->Setkeyflg(false);

}

TitleScene::~TitleScene()
{

}

void TitleScene::Update()
{


	GM->FadeIn(Fade);

	if (!GM->GetFadein())
	{
		Input::Get()->Setkeyflg(true);
	}

	Dome->Update();

	goal->TitleUpdate();

	Cam->FocusCamera(Book->Getpos(), 0.5f ,0.0f);

	if (Input::Get()->GetKeyTrigger(DIK_SPACE) && !GM->GetFadein())
	{
		this->FadeOut = true;
	}

	if (this->FadeOut)
	{
		GM->FadeOut(Fade);
		if (!GM->GetFadeout())
		{
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT);
		}
	}

}

void TitleScene::Draw()
{

	Dome->Draw();

	//goal->Draw();

	Book->Draw();

	GR->Draw();

	UI2->Draw();

	Fade->Draw();

	Cam->Draw();

}

void TitleScene::Init()
{

}

void TitleScene::UnInit()
{

	delete goal;
	goal = nullptr;

	delete Book;
	Book = nullptr;

	delete Cam;
	Cam = nullptr;

	delete Dome;
	Dome = nullptr;

	delete GR;
	GR = nullptr;

	delete UI2;
	UI2 = nullptr;

	delete Fade;
	Fade = nullptr;

	delete GM;
	GM = nullptr;



}

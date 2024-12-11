#include "ResultScene.h"
#include "CSceneManager.h"
#include "Input.h"

ResultScene::ResultScene()
{
	Cam = new Camera(Vector3(0.0f, 200.0f, 0.0f));
	Cam->SetFoucus(Vector3(0.0f, 0.0f, 0.0f));
}

ResultScene::~ResultScene()
{

}

void ResultScene::Update()
{
	if (Input::Get()->GetKeyPress(DIK_SPACE))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
	}
}

void ResultScene::Draw()
{
	Cam->Draw();
}

void ResultScene::Init()
{

}

void ResultScene::UnInit()
{

	delete Cam;
	Cam = nullptr;

}

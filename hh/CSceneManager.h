#pragma once
#include "CTest.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "STAGE1.h"
#include "STAGE2.h"
#include "SelectScene.h"

//シーンの種類
enum class SCENE_ID
{
	TITLE,
	RESALT,
	TEST,
	STAGE_1,
	STAGE_2,
	SELECT,
};

class CSceneManager
{
private:
	//シングルトン
	CSceneManager();
	~CSceneManager();

	// 現在のシーンのポインタ
	CScene* currentScene;

	//現在のシーン
	SCENE_ID NowScene = SCENE_ID::TITLE;
	//次のシーン
	SCENE_ID nextScene;

	static CSceneManager* instance;

public:

	//インスタンスを取得するための関数
	static CSceneManager* GetInstance();

	//シーン切り替え用
	void ChangeScene(SCENE_ID scene);

	static void CleanupSingleton();

	void Init();
	void Update();
	void Draw();
	void Dis();
};


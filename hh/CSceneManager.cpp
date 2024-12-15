#include "CSceneManager.h"

// static メンバ変数の定義
CSceneManager* CSceneManager::instance = nullptr;

CSceneManager::CSceneManager() : currentScene(nullptr),NowScene(SCENE_ID::TITLE),nextScene(SCENE_ID::TITLE)
{

}

CSceneManager::~CSceneManager()
{
    // 現在のシーンが存在すれば解放
    if (currentScene)
    {
        currentScene->UnInit();
        delete currentScene;
        currentScene = nullptr;
    }
}

void CSceneManager::CleanupSingleton()
{
    // インスタンスがあるなら解放
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

CSceneManager* CSceneManager::GetInstance()
{
    // シングルトンが存在していないなら生成
    if (!instance)
    {
        // シングルトンの生成
        instance = new CSceneManager();
    }
    //唯一のインスタンスを返す
    return instance;
}

void CSceneManager::ChangeScene(SCENE_ID _scene)
{

    // 現在のシーンを解放
    if (currentScene)
    {
        currentScene->UnInit();
        delete currentScene;
        currentScene = nullptr;
    }

    // 新しいシーンを設定
    NowScene = _scene;

    // 新しいシーンを初期化
    switch (NowScene)
    {
    case SCENE_ID::TEST:
        currentScene = new CTest();
        break;
    case SCENE_ID::STAGE_1:
        currentScene = new STAGE1();
        break;
    case SCENE_ID::ANIM:
        currentScene = new AnimScene();
        break;
    case SCENE_ID::TITLE:
        currentScene = new TitleScene();
        break;
    case SCENE_ID::RESALT:
        currentScene = new ResultScene();
        break;
    case SCENE_ID::SELECT:
        currentScene = new SelectScene();
        break;
    }

    if (currentScene)
    {
        currentScene->Init();
    }
}

void CSceneManager::Init()
{
    ChangeScene(NowScene);
}

void CSceneManager::Update()
{
    if (currentScene)
    {
        currentScene->Update();
    }

}

void CSceneManager::Draw()
{
    if (currentScene)
    {
        currentScene->Draw();
    }

}

void CSceneManager::Dis()
{
    if (currentScene)
    {
        currentScene->UnInit();
        delete currentScene;
        currentScene = nullptr;
    }
}


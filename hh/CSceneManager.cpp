#include "CSceneManager.h"

// static メンバ変数の定義
CSceneManager* CSceneManager::instance = nullptr;

CSceneManager::CSceneManager() : currentScene(nullptr), m_Fade(nullptr), NowScene(SCENE_ID::TITLE)
{
    m_Fade = new Fade();  // フェードオブジェクトを初期化
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
    // フェードオブジェクトを解放
    if (m_Fade)
    {
        delete m_Fade;
        m_Fade = nullptr;
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
    // フェードアウト開始
    StartFadeOut();

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
    }

    if (currentScene)
    {
        currentScene->Init();
    }

    // フェードイン開始
    StartFadeIn();
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

    // フェードの更新
    if (m_Fade)
    {
        m_Fade->Update();
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

void CSceneManager::StartFadeIn()
{
    if (m_Fade)
    {
        m_Fade->FadeIn();  // フェードイン開始
    }
}

void CSceneManager::StartFadeOut()
{
    if (m_Fade)
    {
        m_Fade->FadeOut();  // フェードアウト開始
    }
}


#include "CSceneManager.h"

// static �����o�ϐ��̒�`
CSceneManager* CSceneManager::instance = nullptr;

CSceneManager::CSceneManager() : currentScene(nullptr),NowScene(SCENE_ID::TITLE),nextScene(SCENE_ID::TITLE)
{

}

CSceneManager::~CSceneManager()
{
    // ���݂̃V�[�������݂���Ή��
    if (currentScene)
    {
        currentScene->UnInit();
        delete currentScene;
        currentScene = nullptr;
    }
}

void CSceneManager::CleanupSingleton()
{
    // �C���X�^���X������Ȃ���
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

CSceneManager* CSceneManager::GetInstance()
{
    // �V���O���g�������݂��Ă��Ȃ��Ȃ琶��
    if (!instance)
    {
        // �V���O���g���̐���
        instance = new CSceneManager();
    }
    //�B��̃C���X�^���X��Ԃ�
    return instance;
}

void CSceneManager::ChangeScene(SCENE_ID _scene)
{

    // ���݂̃V�[�������
    if (currentScene)
    {
        currentScene->UnInit();
        delete currentScene;
        currentScene = nullptr;
    }

    // �V�����V�[����ݒ�
    NowScene = _scene;

    // �V�����V�[����������
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


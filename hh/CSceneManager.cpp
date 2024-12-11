#include "CSceneManager.h"

// static �����o�ϐ��̒�`
CSceneManager* CSceneManager::instance = nullptr;

CSceneManager::CSceneManager() : currentScene(nullptr), m_Fade(nullptr), NowScene(SCENE_ID::TITLE)
{
    m_Fade = new Fade();  // �t�F�[�h�I�u�W�F�N�g��������
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
    // �t�F�[�h�I�u�W�F�N�g�����
    if (m_Fade)
    {
        delete m_Fade;
        m_Fade = nullptr;
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
    // �t�F�[�h�A�E�g�J�n
    StartFadeOut();

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
    }

    if (currentScene)
    {
        currentScene->Init();
    }

    // �t�F�[�h�C���J�n
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

    // �t�F�[�h�̍X�V
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
        m_Fade->FadeIn();  // �t�F�[�h�C���J�n
    }
}

void CSceneManager::StartFadeOut()
{
    if (m_Fade)
    {
        m_Fade->FadeOut();  // �t�F�[�h�A�E�g�J�n
    }
}


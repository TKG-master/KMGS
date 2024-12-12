#pragma once
#include "CTest.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "AnimScene.h"
#include "STAGE1.h"
#include "SelectScene.h"
#include "Fade.h"

//�V�[���̎��
enum class SCENE_ID
{
	TITLE,
	RESALT,
	TEST,
	STAGE_1,
	SELECT,
	ANIM,
};

class CSceneManager
{
private:
	//�V���O���g��
	CSceneManager();
	~CSceneManager();

	// ���݂̃V�[���̃|�C���^
	CScene* currentScene;

	// �t�F�[�h�I�u�W�F�N�g
	Fade* m_Fade;

	//���݂̃V�[��
	SCENE_ID NowScene = SCENE_ID::TITLE;

	static CSceneManager* instance;

public:

	//�C���X�^���X���擾���邽�߂̊֐�
	static CSceneManager* GetInstance();

	//�V�[���؂�ւ��p
	void ChangeScene(SCENE_ID scene);

	static void CleanupSingleton();

	void Init();
	void Update();
	void Draw();
	void Dis();

	// �t�F�[�h�̊J�n�i�t�F�[�h�C���j
	void StartFadeIn();

	// �t�F�[�h�̊J�n�i�t�F�[�h�A�E�g�j
	void StartFadeOut();
};


#pragma once
#include "CTest.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "STAGE1.h"
#include "STAGE2.h"
#include "SelectScene.h"

//�V�[���̎��
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
	//�V���O���g��
	CSceneManager();
	~CSceneManager();

	// ���݂̃V�[���̃|�C���^
	CScene* currentScene;

	//���݂̃V�[��
	SCENE_ID NowScene = SCENE_ID::TITLE;
	//���̃V�[��
	SCENE_ID nextScene;

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
};


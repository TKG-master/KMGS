#pragma once
#include "Timer.h"
#include "easings.h"
#include "CCollision.h"

class Camera;
class Enemy;
class Timer;
class Player;
class GoalObj;
class BoxObj;
class GameUI;


//GameManager

class EasingController
{
private:
	//�ŏ��̃C�[�W���O���Ǘ�����bool�^
	bool startEasing = true;
	bool isEasingStart = true;
	//�N���A���̃C�[�W���O���Ǘ�����bool�^
	bool EndEasing = true;
	//�G�Ɍ����������̃C�[�W���O���Ǘ�����bool�^
	bool RookEasing = true;
	//�ŏ��̃{�b�N�X�̏��������邽�߂�bool�^
	bool startBoxEasing = true;
	//�t�F�[�h���Ǘ�����bool�^
	bool Fadein = true;
	bool Fadeout = true;
	//�ǂɒ���t�����Ƃ��̃J�����̃C�[�W���O
	bool StikyEasing = true;
	//�Z���N�g��ʂ̃C�[�W���O���Ǘ�����bool�^
	bool SelectUIEasing = true;
	//�N���A���̉�ʂ̃C�[�W���O���Ǘ�����bool�^
	bool ClearUIEasingX = true;
	bool ClearUIEasingY = true;
	//�Z���N�g��ʂ̃C���[�W�̃C�[�W���O���Ǘ�����bool�^
	bool ImageUIEasing = true;
	bool ImageEasingEnd = false;


	//�C�[�W���O�̎��Ɏg�����Ԃ̕ϐ�
	float deltaTime = 0.01f;
	float BdeltaTime = 0.05f;
	float deltaTimeStiky = 0.01f;

	float Time1 = 0.00f;
	float StikyTime = 0.00f;
	float EasingStartTime = 0.00f;
	float EnemyTime = 0.00f;
	float GoalTime = 0.00f;
	float Stime = 0.00f;
	float ImageT = 0.00f;

	//�G���������ꍇ�̗]���ȃ��[�v���Ȃ������߂�bool�^
	bool Rookfarst = false;

	bool Goal = false;

	std::vector<BoxObj*> BOXS;
	size_t currentBoxIndex = 0;

public:

	EasingController();
	~EasingController();

	//�J�����̍ŏ��̏���
	bool farstEasing(Camera* camera,Player* Pl,GoalObj* goal);
	//�G�Ɍ����������̃J�����̏���
	bool EnemyEasing(std::vector<Enemy*> enemys, DirectX::SimpleMath::Vector3 PlPos, Camera* camera,Timer* timer);
	//�X�e�[�W�J�n�̃{�b�N�X�̏���
	void farstBoxEasing(std::vector<BoxObj*> boxs);

	bool GetStartEasing() { return this->startEasing; };

	void SetStartBoxEasing(bool B) { this->startBoxEasing = B; };
	bool GetStartBoxEasing() { return this->startBoxEasing; };

	void GameEnd(std::vector<Enemy*> enemys , GoalObj* goal);

	bool GetGoal() { return this->Goal; };
	void SetGoal(bool flg) { this->Goal = flg; };

	void GoalEasing(DirectX::SimpleMath::Vector3 Plpos, Camera* camera);

	bool GetEndEasing() { return this->EndEasing; };
	void SetEndEasing(bool flg) { this->EndEasing = flg; };

	bool SEasing(Player* Pl, Camera* camera);

	void FadeIn(GameUI* FadeUI);

	void FadeOut(GameUI* FadeUI);

	void ClearEasing(GameUI* Clear);

	void ImageEasing(GameUI* Image);

	void SelectEasing(GameUI* Select);

	bool GetFadein() { return this->Fadein; };
	bool GetFadeout() { return this->Fadeout; };

	void SetStikyEasing(bool flg) { this->StikyEasing = flg; };
	bool GetStikyEasing() { return this->StikyEasing; };

	bool GetisEasingstart() { return this->isEasingStart; };

	bool GetClearUIEasingX() { return this->ClearUIEasingX; };
	bool GetClearUIEasingY() { return this->ClearUIEasingY; };

	bool GetImageUIEasing() { return this->ImageUIEasing; };
	void SetImageUIEasing(bool flg) { this->ImageUIEasing = flg; };
	bool GetImageEasingEnd() { return this->ImageEasingEnd; }
	void SetImageEasingEnd(bool flg) { this->ImageEasingEnd = flg; };



};


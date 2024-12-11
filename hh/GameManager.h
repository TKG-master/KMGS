#pragma once
#include "Timer.h"
#include "easings.h"

class Camera;
class Enemy;
class Timer;
class Player;
class GoalObj;
class BoxObj;




class GameManager
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
	//�C�[�W���O�̎��Ɏg�����Ԃ̕ϐ�
	float deltaTime = 0.010f;
	float BdeltaTime = 0.05f;
	float Time1 = 0.01f;
	//�G���������ꍇ�̗]���ȃ��[�v���Ȃ������߂�bool�^
	bool Rookfarst = false;

	bool Goal = false;

	std::vector<BoxObj*> BOXS;
	size_t currentBoxIndex = 0;

public:

	GameManager();
	~GameManager();

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




};


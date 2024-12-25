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




class GameManager
{
private:
	//最初のイージングを管理するbool型
	bool startEasing = true;
	bool isEasingStart = true;
	//クリア時のイージングを管理するbool型
	bool EndEasing = true;
	//敵に見つかった時のイージングを管理するbool型
	bool RookEasing = true;
	//最初のボックスの処理をするためのbool型
	bool startBoxEasing = true;
	//フェードを管理するbool型
	bool Fadein = true;
	bool Fadeout = true;
	//壁に張り付いたときのカメラのイージング
	bool StikyEasing = true;


	//イージングの時に使う時間の変数
	float deltaTime = 0.01f;
	float BdeltaTime = 0.05f;
	float deltaTimeStiky = 0.001f;

	float Time1 = 0.00f;
	float StikyTime = 0.00f;
	float EasingStartTime = 0.00f;
	float EnemyTime = 0.00f;
	float GoalTime = 0.00f;

	//敵が見つけた場合の余分なループをなくすためのbool型
	bool Rookfarst = false;

	bool Goal = false;

	std::vector<BoxObj*> BOXS;
	size_t currentBoxIndex = 0;

public:

	GameManager();
	~GameManager();

	//カメラの最初の処理
	bool farstEasing(Camera* camera,Player* Pl,GoalObj* goal);
	//敵に見つかった時のカメラの処理
	bool EnemyEasing(std::vector<Enemy*> enemys, DirectX::SimpleMath::Vector3 PlPos, Camera* camera,Timer* timer);
	//ステージ開始のボックスの処理
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

	bool GetFadein() { return this->Fadein; };
	bool GetFadeout() { return this->Fadeout; };

	void SetStikyEasing(bool flg) { this->StikyEasing = flg; };
	bool GetStikyEasing() { return this->StikyEasing; };



};


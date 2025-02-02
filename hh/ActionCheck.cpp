#include "ActionCheck.h"
#include "Enemy.h"

bool ActionCheck::Execute(Enemy* enemy)
{
	if (enemy->Getpath().empty() || enemy->GetPathIndex() >= enemy->Getpath().size()) {
		//アイドルのアニメーション
		if (enemy->GetAstatus() != IDLE)
		{
			enemy->SetAstatus(IDLE);
		}
		//探し終わった後の初期化
		enemy->SetSearch(false);
		enemy->SethearSound(false);
		//タイマーのリセット
		enemy->GetTimer()->Reset();
		//現在の状態に合わせた処理をする
		//探しに行ったなら持ち場に戻る
		if (enemy->GetState() == EStateType::Serch)
		{
			enemy->ChangeState(EStateType::Back);
			return false;
		}
		//持ち場に戻ると巡回を続ける
		else if (enemy->GetState() == EStateType::Back)
		{
			if (enemy->GetTypeSecrity() == false)
			{
				enemy->ChangeState(EStateType::Patrolling);
				enemy->SetWaypointIndex(0);
				return false;
			}
			else if (enemy->GetTypeSecrity() == true)
			{
				enemy->ChangeState(EStateType::Fixed);
				return false;
			}
		}
		else if (enemy->GetState() == EStateType::Bookconnection)
		{
			enemy->ChangeState(EStateType::BookRead);
			enemy->SetbookRead(true);
			return false;
		}
	}
	return true;
}

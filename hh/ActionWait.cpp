#include "ActionWait.h"
#include "enemy.h"

bool ActionWait::Execute(Enemy* enemy)
{

	//少し待つ
	if (!enemy->GetTimer()->IsRunning()) {
		enemy->GetTimer()->StartCountDown(1.0f);
	}
	//待ち終わったら
	if (enemy->GetTimer()->IsTimeUp())
	{
		return true;
	}
	//待っている間のアニメーション
	else
	{
		if (enemy->GetAstatus() != IDLE)
		{
			enemy->SetAstatus(IDLE);
		}
	}


	return false;
}

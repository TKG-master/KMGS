#include "ActionConcern.h"
#include "Enemy.h"

bool ActionConcern::Execute(Enemy* enemy)
{
	if (enemy->GetSearch()) {
		return false;  // 徘徊状態でない場合、処理しない
	}

    if (enemy->GetAstatus() != IDLE)
    {
        enemy->SetAstatus(IDLE);
    }
    else if (enemy->GetAstatus() == IDLE)
    {
        enemy->SetToAnimationName("Idle");
    }

	enemy->securityMove();

	return true;
}

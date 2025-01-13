#include "ActionConcern.h"
#include "Enemy.h"

bool ActionConcern::Execute(Enemy* enemy)
{
	if (enemy->GetSearch() || enemy->GetRookBook() || enemy->GetbookRead() || enemy->GetState() != EStateType::Fixed) {
		return false;
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

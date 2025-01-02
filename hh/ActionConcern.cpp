#include "ActionConcern.h"
#include "Enemy.h"

bool ActionConcern::Execute(Enemy* enemy)
{
	if (enemy->GetSearch()) {
		return false;  // œpœjó‘Ô‚Å‚È‚¢ê‡Aˆ—‚µ‚È‚¢
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

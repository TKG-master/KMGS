#include "ActionConcern.h"
#include "Enemy.h"

bool ActionConcern::Execute(Enemy* enemy)
{
	if (enemy->GetState() != EStateType::Fixed) {
		return false;  // œpœjó‘Ô‚Å‚È‚¢ê‡Aˆ—‚µ‚È‚¢
	}

	enemy->securityMove();

	return true;
}

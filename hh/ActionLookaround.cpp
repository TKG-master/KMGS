#include "ActionLookaround.h"
#include "Enemy.h"

bool ActionLookaround::Execute(Enemy* enemy)
{
	if (enemy->GetState() != EStateType::Lookaround)
	{
		return false;
	}

	enemy->lookaround();
	return true;
}

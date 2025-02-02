#include "ActionCheckState.h"
#include "Enemy.h"

bool ActionCheckState::Execute(Enemy* enemy)
{
	return enemy->GetState() == requiredState;

}

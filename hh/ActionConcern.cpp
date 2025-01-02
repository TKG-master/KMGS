#include "ActionConcern.h"
#include "Enemy.h"

bool ActionConcern::Execute(Enemy* enemy)
{
	if (enemy->GetSearch()) {
		return false;  // �p�j��ԂłȂ��ꍇ�A�������Ȃ�
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

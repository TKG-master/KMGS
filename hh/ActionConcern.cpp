#include "ActionConcern.h"
#include "Enemy.h"

bool ActionConcern::Execute(Enemy* enemy)
{
	if (enemy->GetState() != EStateType::Patrolling) {
		return false;  // �p�j��ԂłȂ��ꍇ�A�������Ȃ�
	}

	return false;
}

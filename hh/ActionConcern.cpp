#include "ActionConcern.h"
#include "Enemy.h"

bool ActionConcern::Execute(Enemy* enemy)
{
	if (enemy->GetSearch()) {
		return false;  // �p�j��ԂłȂ��ꍇ�A�������Ȃ�
	}

	enemy->securityMove();

	return true;
}

#include "ActionConcern.h"
#include "Enemy.h"

bool ActionConcern::Execute(Enemy* enemy)
{
	if (enemy->GetSearch()) {
		return false;  // 徘徊状態でない場合、処理しない
	}

	enemy->securityMove();

	return true;
}

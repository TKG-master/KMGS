#include "ActionConcern.h"
#include "Enemy.h"

bool ActionConcern::Execute(Enemy* enemy)
{
	if (enemy->GetState() != EStateType::Patrolling) {
		return false;  // 徘徊状態でない場合、処理しない
	}



	return false;
}

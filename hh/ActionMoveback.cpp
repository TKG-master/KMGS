#include "ActionMoveback.h"
#include "Enemy.h"

bool ActionMoveback::Execute(Enemy* enemy)
{
    // 徘徊モードのロジックを処理
    if (enemy->GetState() != EStateType::Patrolling) {
        return false;  // 徘徊状態でない場合、処理しない
    }

    if(enemy->Getback())
    {
        enemy->FollowPath();
    }

    return true;
}

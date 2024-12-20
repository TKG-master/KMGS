#include "ActionMoveSearch.h"
#include "Enemy.h"

bool ActionMoveSearch::Execute(Enemy* enemy)
{
    // 徘徊モードのロジックを処理
    if (enemy->GetState() != EStateType::Patrolling) {
        return false;  // 徘徊状態でない場合、処理しない
    }

    if (enemy->GetAstatus() == WALK)
    {
        enemy->SetToAnimationName("Walk");
    }
    else if (enemy->GetAstatus() != WALK)
    {
        enemy->SetAstatus(WALK);
    }

    if (enemy->GetSearch())
    {
        enemy->FollowPath();
        return true;
    }

    return false;
}

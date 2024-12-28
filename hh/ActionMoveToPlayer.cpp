#include "ActionMoveToPlayer.h"
#include "Enemy.h"

bool ActionMoveToPlayer::Execute(Enemy* enemy) {
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

    if (!enemy->GetSearch() && !enemy->Getback())
    {
        enemy->Wanderaround();
        return true;
    }

    return false;

    //enemy->PatrollingMove();
    //return true;  // 処理が成功した
}
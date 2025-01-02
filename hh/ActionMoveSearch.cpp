#include "ActionMoveSearch.h"
#include "Enemy.h"

bool ActionMoveSearch::Execute(Enemy* enemy)
{
    // 徘徊モードのロジックを処理
    //if (enemy->GetState() == EStateType::Patrolling) {
    //    return false;  // 徘徊状態でない場合、処理しない
    //}
    if (!enemy->GetSearch())
    {
        return false;
    }
    //探しに行くときのif文
    else if (enemy->GetSearch())
    {
        //少し時間を待ってから探しに行く
        if (!enemy->GetTimer()->IsRunning()) {
            enemy->GetTimer()->StartCountDown(1.5f);
        }
        //待つ時間が終わったら
        if (enemy->GetTimer()->IsTimeUp())
        {
            if (enemy->GetAstatus() != WALK)
            {
                enemy->SetAstatus(WALK);
            }
            else if (enemy->GetAstatus() == WALK)
            {
                enemy->SetToAnimationName("Walk");
            }
            //パスを受け取って探しに行く
            enemy->FollowPath();
        }
        else {
            //待っている間は立モーション
            if (enemy->GetAstatus() != IDLE)
            {
                enemy->SetAstatus(IDLE);
            }
            else if (enemy->GetAstatus() == IDLE)
            {
                enemy->SetToAnimationName("Idle");
            }
        }
        return true;
    }

    return false;
}

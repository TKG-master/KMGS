#include "ActionBookRook.h"
#include "Enemy.h"

bool ActionBookRook::Execute(Enemy* enemy)
{
    if (!enemy->GetRookBook())
    {
        return false;
    }
    else if (enemy->GetRookBook())
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

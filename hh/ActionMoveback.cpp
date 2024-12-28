#include "ActionMoveback.h"
#include "Enemy.h"

bool ActionMoveback::Execute(Enemy* enemy)
{
    if (!enemy->Getback())
    {
        return false;
    }

    else if(enemy->Getback())
    {
       //少し時間を待ってから帰る
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
            //パスを受け取って帰る
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

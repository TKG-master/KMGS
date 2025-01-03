#include "ActionRead.h"
#include "Enemy.h"

bool ActionRead::Execute(Enemy* enemy)
{
    if (!enemy->GetbookRead())
    {
        return false;
    }
    
    //10秒止まって戻る処理を書く
    if (!enemy->GetTimer()->IsRunning()) {
        enemy->GetTimer()->StartCountDown(10.0f);
    }
    if (enemy->GetTimer()->IsTimeUp())
    {
        enemy->SetbookRead(false);
        enemy->Setback(true);
    }
    else
    {
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

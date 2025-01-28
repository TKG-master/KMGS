#include "ActionRead.h"
#include "Enemy.h"

bool ActionRead::Execute(Enemy* enemy)
{
    if (!enemy->GetbookRead())
    {
        return false;
    }
    
    //10�b�~�܂��Ė߂鏈��������
    if (!enemy->GetTimer()->IsRunning()) {
        enemy->GetTimer()->StartCountDown(enemy->GetBookReadTime());
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

#include "ActionBookRead.h"
#include "Enemy.h"

bool ActionBookRead::Execute(Enemy* enemy)
{

    if (enemy->GetAstatus() != IDLE)
    {
        enemy->SetAstatus(IDLE);
    }
    //10�b�~�܂��Ė߂鏈��������
    if (!enemy->GetTimer()->IsRunning()) {
        enemy->GetTimer()->StartCountDown(enemy->GetBookReadTime());
    }

    if (enemy->GetTimer()->IsTimeUp())
    {
        enemy->SetbookRead(false);
        enemy->ChangeState(EStateType::Back);
        return true;
    }

    return false;
}

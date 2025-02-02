#include "ActionBookRead.h"
#include "Enemy.h"

bool ActionBookRead::Execute(Enemy* enemy)
{

    if (enemy->GetAstatus() != IDLE)
    {
        enemy->SetAstatus(IDLE);
    }
    //10•b~‚Ü‚Á‚Ä–ß‚éˆ—‚ğ‘‚­
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

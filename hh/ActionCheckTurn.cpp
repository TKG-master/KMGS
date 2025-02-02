#include "ActionCheckTurn.h"
#include "Enemy.h"

bool ActionCheckTurn::Execute(Enemy* enemy)
{
    if (enemy->GetState() == EStateType::Fixed)
    {
        enemy->ChangeState(EStateType::FixedLeft);
    }
    else if (enemy->GetState() == EStateType::FixedLeft)
    {
        enemy->ChangeState(EStateType::Fixed);
    }
    
    enemy->GetTimer()->Reset();
    return true;
}

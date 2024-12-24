#include "ActionFixed.h"
#include "Enemy.h"
bool ActionFixed::Execute(Enemy* enemy)
{
    if (enemy->GetState() != EStateType::Fixed)
    {
        return false;
    }



    return false;
}

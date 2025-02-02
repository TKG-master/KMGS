#include "ActionCheckArrival.h"
#include "Enemy.h"

bool ActionCheckArrival::Execute(Enemy* enemy)
{

    float distance = (enemy->GetTargetPos() - enemy->GetPosition()).Length();

    if (distance < enemy->GetMoveSpeed() * 2.5f) {
        return true;
    }
    return false;
}

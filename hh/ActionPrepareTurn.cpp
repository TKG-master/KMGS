#include "ActionPrepareTurn.h"
#include "Enemy.h"

bool ActionPrepareTurn::Execute(Enemy* enemy)
{
    if (enemy->GetState() == EStateType::Turn) {
        return true;  // すでにターン状態ならそのまま進む
    }


    return false;
}

#include "ActionPrepareTurn.h"
#include "Enemy.h"

bool ActionPrepareTurn::Execute(Enemy* enemy)
{
    if (enemy->GetState() == EStateType::Turn) {
        return true;  // ‚·‚Å‚Éƒ^[ƒ“ó‘Ô‚È‚ç‚»‚Ì‚Ü‚Üi‚Ş
    }


    return false;
}

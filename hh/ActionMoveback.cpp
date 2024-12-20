#include "ActionMoveback.h"
#include "Enemy.h"

bool ActionMoveback::Execute(Enemy* enemy)
{
    // œpœjƒ‚[ƒh‚ÌƒƒWƒbƒN‚ðˆ—
    if (enemy->GetState() != EStateType::Patrolling) {
        return false;  // œpœjó‘Ô‚Å‚È‚¢ê‡Aˆ—‚µ‚È‚¢
    }

    if(enemy->Getback())
    {
        enemy->FollowPath();
    }

    return true;
}

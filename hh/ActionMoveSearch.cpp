#include "ActionMoveSearch.h"
#include "Enemy.h"

bool ActionMoveSearch::Execute(Enemy* enemy)
{
    // œpœjƒ‚[ƒh‚ÌƒƒWƒbƒN‚ðˆ—
    if (enemy->GetState() != EStateType::Patrolling) {
        return false;  // œpœjó‘Ô‚Å‚È‚¢ê‡Aˆ—‚µ‚È‚¢
    }

    if (enemy->GetAstatus() == WALK)
    {
        enemy->SetToAnimationName("Walk");
    }
    else if (enemy->GetAstatus() != WALK)
    {
        enemy->SetAstatus(WALK);
    }

    if (enemy->GetSearch())
    {
        enemy->FollowPath();
        return true;
    }

    return false;
}

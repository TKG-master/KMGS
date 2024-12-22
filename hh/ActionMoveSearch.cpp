#include "ActionMoveSearch.h"
#include "Enemy.h"

bool ActionMoveSearch::Execute(Enemy* enemy)
{
    // œpœjƒ‚[ƒh‚ÌƒƒWƒbƒN‚ðˆ—
    if (enemy->GetState() != EStateType::Patrolling) {
        return false;  // œpœjó‘Ô‚Å‚È‚¢ê‡Aˆ—‚µ‚È‚¢
    }
    //’T‚µ‚És‚­‚Æ‚«‚Ìif•¶
    if (enemy->GetSearch())
    {
        //­‚µŽžŠÔ‚ð‘Ò‚Á‚Ä‚©‚ç’T‚µ‚És‚­
        if (!enemy->GetTimer()->IsRunning()) {
            enemy->GetTimer()->StartCountDown(1.5f);
        }
        //‘Ò‚ÂŽžŠÔ‚ªI‚í‚Á‚½‚ç
        if (enemy->GetTimer()->IsTimeUp())
        {
            if (enemy->GetAstatus() != WALK)
            {
                enemy->SetAstatus(WALK);
            }
            else if (enemy->GetAstatus() == WALK)
            {
                enemy->SetToAnimationName("Walk");
            }
            //ƒpƒX‚ðŽó‚¯Žæ‚Á‚Ä’T‚µ‚És‚­
            enemy->FollowPath();
        }
        else {
            //‘Ò‚Á‚Ä‚¢‚éŠÔ‚Í—§ƒ‚[ƒVƒ‡ƒ“
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

    return false;
}

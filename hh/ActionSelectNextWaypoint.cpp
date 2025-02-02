#include "ActionSelectNextWaypoint.h"
#include "Enemy.h"

bool ActionSelectNextWaypoint::Execute(Enemy* enemy)
{


    if (enemy->GetwanderingPath().empty()) {
        return false;  // パスがない場合は失敗
    }

    if (enemy->GetAstatus() != WALK)
    {
        enemy->SetAstatus(WALK);
    }

    // 目的地を更新
    enemy->SetTargetPos(enemy->GetwanderingPath()[enemy->GetWaypointIndex()]);

    return true;
}

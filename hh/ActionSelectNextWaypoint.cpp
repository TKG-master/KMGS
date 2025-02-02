#include "ActionSelectNextWaypoint.h"
#include "Enemy.h"

bool ActionSelectNextWaypoint::Execute(Enemy* enemy)
{


    if (enemy->GetwanderingPath().empty()) {
        return false;  // �p�X���Ȃ��ꍇ�͎��s
    }

    if (enemy->GetAstatus() != WALK)
    {
        enemy->SetAstatus(WALK);
    }

    // �ړI�n���X�V
    enemy->SetTargetPos(enemy->GetwanderingPath()[enemy->GetWaypointIndex()]);

    return true;
}

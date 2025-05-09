#include "ActionPerformTurn.h"
#include "Enemy.h"
#include "easings.h"

bool ActionPerformTurn::Execute(Enemy* enemy)
{

    // 回転を実行
    enemy->Setforward(EaseInCirc(enemy->Getforward(), DirectX::SimpleMath::Vector3(0.0f, 0.0f, -1.0f), enemy->GetTime1()));

    // 時間を加算
    enemy->SetTime1(enemy->GetTime1() + enemy->Getdeltatime());

    // まだ回転中なら継続
    if (enemy->GetTime1() < 1.0f) {
        return false;
    }

    else if (enemy->GetTime1() >= 1.0f)
    {
        if (enemy->GetAstatus() != IDLE)
        {
            enemy->SetAstatus(IDLE);
        }
        else if (enemy->GetAstatus() == IDLE)
        {
            enemy->SetToAnimationName("Idle");
        }
        if (enemy->GetWaypointIndex() >= enemy->GetwanderingPath().size())
        {
            enemy->SetWaypointIndex(0);
        }
        enemy->GetTimer()->Reset();
        enemy->ChangeState(EStateType::Patrolling);
        return true;
    }
}

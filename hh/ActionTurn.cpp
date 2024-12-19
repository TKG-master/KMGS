#include "ActionTurn.h"
#include "Enemy.h"
#include "easings.h"

using namespace DirectX::SimpleMath;

bool ActionTurn::Execute(Enemy* enemy)
{
    //ステートがターンでなければfalseを返す
    if (enemy->GetState() != EStateType::Turn)
    {
        return false;
    }

    enemy->Setforward(EaseInCirc(enemy->Getforward(), Vector3(0.0f, 0.0f, -1.0f), enemy->GetTime()));
    enemy->SetTime(enemy->GetTime() + enemy->Getdeltatime());
    if (enemy->GetTime() >= 1.0f) {
        enemy->SetTime(0.5f);
        enemy->SetState(EStateType::Patrolling);
        return true;
    }
}

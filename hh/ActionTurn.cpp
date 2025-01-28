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

    enemy->Setforward(EaseInCirc(enemy->Getforward(), Vector3(0.0f, 0.0f, -1.0f), enemy->GetTime1()));
    enemy->SetTime1(enemy->GetTime1() + enemy->Getdeltatime());
    if (enemy->GetTime1() >= 1.0f) {
        enemy->SetTime1(0.0f);
        enemy->SetState(EStateType::Patrolling);
        return true;
    }

    return false;

}

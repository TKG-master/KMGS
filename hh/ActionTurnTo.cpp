#include "ActionTurnTo.h"
#include "Enemy.h"
#include "easings.h"

bool ActionTurnTo::Execute(Enemy* enemy)
{

    DirectX::SimpleMath::Vector3 targetDirection = (num == 0) ? enemy->Getforwardpath()[0] : enemy->Getforwardpath()[1];


    enemy->Setforward(EaselnQuart(enemy->Getforward(), enemy->Getforwardpath()[num], enemy->GetTime()));
    enemy->SetTime(enemy->GetTime() + enemy->Getdeltatime());

    //回転終了なら
    if (enemy->GetTime() >= 1.0f) {
        enemy->SetTime(0.0f);
        return true;
    }
    //回転が終わっていないなら
    return false;
}

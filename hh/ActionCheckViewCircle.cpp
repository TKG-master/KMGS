#include "ActionCheckViewCircle.h"
#include "Enemy.h"

//bool ActionCheckViewCircle::Execute(Enemy* enemy)
//{
//    //なんとなく見えている距離
//    if (enemy->InInViewCircle(enemy->GetPosition(), enemy->PositionForward(), enemy->GetFov(), playerdate->GetPosition(), 10.0f, enemy->Getlength() * 1.5f) && !enemy->GetbookRead())
//    {
//        if (enemy->RayLookHit())
//        {
//            enemy->ChangeState(EStateType::Serch);
//            enemy->SetSearch(true);
//        }
//    }
//    //絶対に見つかる距離
//    if (enemy->InInViewCircle(enemy->GetPosition(), enemy->PositionForward(), enemy->GetFov(), Pl->GetPosition(), 10.0f, enemy->Getlength()) && !enemy->GetbookRead())
//    {
//        if (enemy->RayLookHit())
//        {
//            enemy->SetTest(true);
//        }
//    }
//}

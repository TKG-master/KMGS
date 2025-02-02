#include "ActionLookaround.h"
#include "Enemy.h"

bool ActionLookaround::Execute(Enemy* enemy)
{
    
    if (enemy->GetAstatus() != IDLE)
    {
        enemy->SetAstatus(IDLE);
    }

    // タイマーがまだ開始されていない場合に開始する
    if (!enemy->GetTimer()->IsRunning()) {
        enemy->GetTimer()->StartCountDown(1.5f);
    }

    if (enemy->GetTimer()->IsTimeUp())
    {
        //タイマーリセット
        enemy->GetTimer()->Reset();
        //次の地点の設定
        enemy->NextWaypointIndex();
        //時間を0.0fに
        enemy->SetTime1(0.0f);
        //Stateを変更
        enemy->ChangeState(EStateType::Turn);
        return true;
    }
    return false;
}

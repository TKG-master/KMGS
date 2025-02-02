#include "ActionSerchMove.h"
#include "Enemy.h"

bool ActionPathMove::Execute(Enemy* enemy)
{

    if (enemy->GetAstatus() != WALK)
    {
        enemy->SetAstatus(WALK);
    }

    // 目標地点を取得
    DirectX::SimpleMath::Vector3 targetPos = enemy->Getpath()[enemy->GetPathIndex()];
    DirectX::SimpleMath::Vector3 currentPosition = enemy->GetPosition();

    // 移動量を計算
    DirectX::SimpleMath::Vector3 direction = targetPos - currentPosition;
    float distance = direction.Length();

    // 許容範囲内なら次のポイントへ
    float tolerance = enemy->GetMoveSpeed() * 2.5f;
    if (distance < tolerance) {
        enemy->SetPosition(targetPos);
        if (enemy->GetPathIndex() <= enemy->Getpath().size())
        {
            enemy->SetPathIndex(enemy->GetPathIndex() + 1);
        }
        return true;
    }

    // 方向を正規化し、移動
    direction.Normalize();
    enemy->SetPosition(currentPosition + direction * enemy->GetMoveSpeed() * 1.5f);

    // 進行方向に向けて回転を更新
    if (direction.LengthSquared() > 0.0f) {
        //向きをセット
        enemy->Setforward(direction);
        enemy->UpdateRotation();  // 回転の更新
    }

    return false;

}

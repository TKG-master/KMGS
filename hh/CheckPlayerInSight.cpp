#include "CheckPlayerInSight.h"
#include "Enemy.h"
#include "player.h"

bool CheckPlayerInSight::Execute(Enemy* enemy) {
    // プレイヤーが視界内にいるかどうかをチェック
    // 仮のチェック（実際には視界に関する計算を実装）

    return  enemy->IsInView(enemy->GetPosition(), enemy->Getforward(), 60.0f, enemy->getPlayer()->GetPosition(), 50.0f);
}

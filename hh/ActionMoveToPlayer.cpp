#include "ActionMoveToPlayer.h"
#include "Enemy.h"

bool ActionMoveToPlayer::Execute(Enemy* enemy) {
    // 徘徊モードのロジックを処理
    if (enemy->GetState() != EStateType::Patrolling) {
        return false;  // 徘徊状態でない場合、処理しない
    }

    enemy->PatrollingMove();
    return true;  // 処理が成功した
}
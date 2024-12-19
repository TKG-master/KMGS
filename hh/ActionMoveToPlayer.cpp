#include "ActionMoveToPlayer.h"
#include "Enemy.h"

bool ActionMoveToPlayer::Execute(Enemy* enemy) {
    // �p�j���[�h�̃��W�b�N������
    if (enemy->GetState() != EStateType::Patrolling) {
        return false;  // �p�j��ԂłȂ��ꍇ�A�������Ȃ�
    }

    enemy->PatrollingMove();
    return true;  // ��������������
}
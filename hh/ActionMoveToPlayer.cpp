#include "ActionMoveToPlayer.h"
#include "Enemy.h"

bool ActionMoveToPlayer::Execute(Enemy* enemy) {
    // �p�j���[�h�̃��W�b�N������
    if (enemy->GetState() != EStateType::Patrolling) {
        return false;  // �p�j��ԂłȂ��ꍇ�A�������Ȃ�
    }


    if (enemy->GetAstatus() == WALK)
    {
        enemy->SetToAnimationName("Walk");
    }
    else if (enemy->GetAstatus() != WALK)
    {
        enemy->SetAstatus(WALK);
    }

    if (!enemy->GetSearch() && !enemy->Getback())
    {
        enemy->Wanderaround();
        return true;
    }

    return false;

    //enemy->PatrollingMove();
    //return true;  // ��������������
}
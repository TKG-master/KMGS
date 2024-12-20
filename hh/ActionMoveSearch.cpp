#include "ActionMoveSearch.h"
#include "Enemy.h"

bool ActionMoveSearch::Execute(Enemy* enemy)
{
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

    if (enemy->GetSearch())
    {
        enemy->FollowPath();
        return true;
    }

    return false;
}

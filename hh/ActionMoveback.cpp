#include "ActionMoveback.h"
#include "Enemy.h"

bool ActionMoveback::Execute(Enemy* enemy)
{
    // �p�j���[�h�̃��W�b�N������
    if (enemy->GetState() != EStateType::Patrolling) {
        return false;  // �p�j��ԂłȂ��ꍇ�A�������Ȃ�
    }

    if(enemy->Getback())
    {
        enemy->FollowPath();
    }

    return true;
}

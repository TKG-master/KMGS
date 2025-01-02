#include "ActionMoveSearch.h"
#include "Enemy.h"

bool ActionMoveSearch::Execute(Enemy* enemy)
{
    // �p�j���[�h�̃��W�b�N������
    //if (enemy->GetState() == EStateType::Patrolling) {
    //    return false;  // �p�j��ԂłȂ��ꍇ�A�������Ȃ�
    //}
    if (!enemy->GetSearch())
    {
        return false;
    }
    //�T���ɍs���Ƃ���if��
    else if (enemy->GetSearch())
    {
        //�������Ԃ�҂��Ă���T���ɍs��
        if (!enemy->GetTimer()->IsRunning()) {
            enemy->GetTimer()->StartCountDown(1.5f);
        }
        //�҂��Ԃ��I�������
        if (enemy->GetTimer()->IsTimeUp())
        {
            if (enemy->GetAstatus() != WALK)
            {
                enemy->SetAstatus(WALK);
            }
            else if (enemy->GetAstatus() == WALK)
            {
                enemy->SetToAnimationName("Walk");
            }
            //�p�X���󂯎���ĒT���ɍs��
            enemy->FollowPath();
        }
        else {
            //�҂��Ă���Ԃ͗����[�V����
            if (enemy->GetAstatus() != IDLE)
            {
                enemy->SetAstatus(IDLE);
            }
            else if (enemy->GetAstatus() == IDLE)
            {
                enemy->SetToAnimationName("Idle");
            }
        }
        return true;
    }

    return false;
}

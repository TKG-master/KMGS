#include "ActionBookRook.h"
#include "Enemy.h"

bool ActionBookRook::Execute(Enemy* enemy)
{
    if (!enemy->GetRookBook())
    {
        return false;
    }
    else if (enemy->GetRookBook())
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

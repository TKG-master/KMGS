#include "ActionMoveback.h"
#include "Enemy.h"

bool ActionMoveback::Execute(Enemy* enemy)
{
    if (!enemy->Getback())
    {
        return false;
    }

    else if(enemy->Getback())
    {
       //�������Ԃ�҂��Ă���A��
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
            //�p�X���󂯎���ċA��
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

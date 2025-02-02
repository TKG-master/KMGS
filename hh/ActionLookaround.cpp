#include "ActionLookaround.h"
#include "Enemy.h"

bool ActionLookaround::Execute(Enemy* enemy)
{
    
    if (enemy->GetAstatus() != IDLE)
    {
        enemy->SetAstatus(IDLE);
    }

    // �^�C�}�[���܂��J�n����Ă��Ȃ��ꍇ�ɊJ�n����
    if (!enemy->GetTimer()->IsRunning()) {
        enemy->GetTimer()->StartCountDown(1.5f);
    }

    if (enemy->GetTimer()->IsTimeUp())
    {
        //�^�C�}�[���Z�b�g
        enemy->GetTimer()->Reset();
        //���̒n�_�̐ݒ�
        enemy->NextWaypointIndex();
        //���Ԃ�0.0f��
        enemy->SetTime1(0.0f);
        //State��ύX
        enemy->ChangeState(EStateType::Turn);
        return true;
    }
    return false;
}

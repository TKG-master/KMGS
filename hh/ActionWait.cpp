#include "ActionWait.h"
#include "enemy.h"

bool ActionWait::Execute(Enemy* enemy)
{

	//�����҂�
	if (!enemy->GetTimer()->IsRunning()) {
		enemy->GetTimer()->StartCountDown(1.0f);
	}
	//�҂��I�������
	if (enemy->GetTimer()->IsTimeUp())
	{
		return true;
	}
	//�҂��Ă���Ԃ̃A�j���[�V����
	else
	{
		if (enemy->GetAstatus() != IDLE)
		{
			enemy->SetAstatus(IDLE);
		}
	}


	return false;
}

#include "ActionCheck.h"
#include "Enemy.h"

bool ActionCheck::Execute(Enemy* enemy)
{
	if (enemy->Getpath().empty() || enemy->GetPathIndex() >= enemy->Getpath().size()) {
		//�A�C�h���̃A�j���[�V����
		if (enemy->GetAstatus() != IDLE)
		{
			enemy->SetAstatus(IDLE);
		}
		//�T���I�������̏�����
		enemy->SetSearch(false);
		enemy->SethearSound(false);
		//�^�C�}�[�̃��Z�b�g
		enemy->GetTimer()->Reset();
		//���݂̏�Ԃɍ��킹������������
		//�T���ɍs�����Ȃ玝����ɖ߂�
		if (enemy->GetState() == EStateType::Serch)
		{
			enemy->ChangeState(EStateType::Back);
			return false;
		}
		//������ɖ߂�Ə���𑱂���
		else if (enemy->GetState() == EStateType::Back)
		{
			if (enemy->GetTypeSecrity() == false)
			{
				enemy->ChangeState(EStateType::Patrolling);
				enemy->SetWaypointIndex(0);
				return false;
			}
			else if (enemy->GetTypeSecrity() == true)
			{
				enemy->ChangeState(EStateType::Fixed);
				return false;
			}
		}
		else if (enemy->GetState() == EStateType::Bookconnection)
		{
			enemy->ChangeState(EStateType::BookRead);
			enemy->SetbookRead(true);
			return false;
		}
	}
	return true;
}

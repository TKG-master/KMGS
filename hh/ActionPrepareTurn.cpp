#include "ActionPrepareTurn.h"
#include "Enemy.h"

bool ActionPrepareTurn::Execute(Enemy* enemy)
{
    if (enemy->GetState() == EStateType::Turn) {
        return true;  // ���łɃ^�[����ԂȂ炻�̂܂ܐi��
    }


    return false;
}

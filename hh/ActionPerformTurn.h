#pragma once
#include "IBehaviorNode.h"
class Enemy;
//�^�[�������s���铮��N���X
class ActionPerformTurn :public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


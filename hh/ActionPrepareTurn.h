#pragma once
#include "IBehaviorNode.h"
class Enemy;
//�U��������߂̃^�[��������N���X
class ActionPrepareTurn : public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


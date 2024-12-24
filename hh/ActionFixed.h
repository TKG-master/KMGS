#pragma once
#include "IBehaviorNode.h"
class Enemy;
class ActionFixed : IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


#pragma once
#include "IBehaviorNode.h"
class Enemy;

class ActionCheckArrival :public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


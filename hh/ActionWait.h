#pragma once
#include "IBehaviorNode.h"
class Enemy;

class ActionWait :public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


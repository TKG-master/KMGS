#pragma once
#include "IBehaviorNode.h"
class Enemy;

class ActionPathMove:public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};

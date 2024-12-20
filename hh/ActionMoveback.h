#pragma once
#include "IBehaviorNode.h"
class Enemy;

class ActionMoveback : public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


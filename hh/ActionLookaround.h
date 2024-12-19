#pragma once
#include "IBehaviorNode.h"
class Enemy;

class ActionLookaround : public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


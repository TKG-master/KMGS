#pragma once
#include "IBehaviorNode.h"
class Enemy;

class ActionMoveSearch : public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


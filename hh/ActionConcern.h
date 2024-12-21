#pragma once
#include "IBehaviorNode.h"
class Enemy;

class ActionConcern : public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


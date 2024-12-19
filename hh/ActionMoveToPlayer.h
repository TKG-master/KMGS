#pragma once
#include "IBehaviorNode.h"

class Enemy;

class ActionMoveToPlayer : public IBehaviorNode {
public:
    bool Execute(Enemy* enemy) override;
};


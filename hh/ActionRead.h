#pragma once
#include "IBehaviorNode.h"

class Enemy;

class ActionRead : public IBehaviorNode
{
public:
    bool Execute(Enemy* enemy) override;
};


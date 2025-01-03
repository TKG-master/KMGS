#pragma once
#include "IBehaviorNode.h"
class Enemy;

class ActionBookRook : public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


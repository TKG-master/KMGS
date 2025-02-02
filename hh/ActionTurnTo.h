#pragma once
#include "IBehaviorNode.h"
#include "SimpleMath.h"
class Enemy;

class ActionTurnTo:public IBehaviorNode
{
private:
    int num = 0;
public:
    ActionTurnTo(int n) : num(n) {}
    bool Execute(Enemy* enemy) override;
};


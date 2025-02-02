#pragma once
#include "IBehaviorNode.h"
#include "Type.h"
class Enemy;

class ActionCheckState:public IBehaviorNode
{
private:
    EStateType requiredState;
public:
    ActionCheckState(EStateType state) : requiredState(state) {}

    bool Execute(Enemy* enemy) override;
};


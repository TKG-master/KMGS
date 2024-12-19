#pragma once
#include "IBehaviorNode.h"

class Enemy;

class ActionTurn : public IBehaviorNode
{
public:
	bool Execute(Enemy* enemy) override;
};


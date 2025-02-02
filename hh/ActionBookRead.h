#pragma once
#include "IBehaviorNode.h"
class Enemy;

class ActionBookRead:public IBehaviorNode
{public:
	bool Execute(Enemy* enemy) override;
};


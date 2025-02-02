#pragma once
#include "IBehaviorNode.h"
class Enemy;

class ActionCheckTurn:public IBehaviorNode
{public:
	bool Execute(Enemy* enemy) override;
};


#pragma once
#include "IBehaviorNode.h"
class Enemy;

class ActionCheckViewCircle : public IBehaviorNode
{public:
	bool Execute(Enemy* enemy) override;
};


#pragma once
#include "IBehaviorNode.h"
class Enemy;
//���̖ړI�n��ݒ肷�铮��N���X
class ActionSelectNextWaypoint :public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


#pragma once
#include "IBehaviorNode.h"
class Enemy;
//�ړI�n�ֈړ����铮��N���X
class ActionMoveToWaypoint :public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


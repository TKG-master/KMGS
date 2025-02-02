#pragma once
#include "IBehaviorNode.h"
class Enemy;
//目的地へ移動する動作クラス
class ActionMoveToWaypoint :public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


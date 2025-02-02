#pragma once
#include "IBehaviorNode.h"
class Enemy;
//次の目的地を設定する動作クラス
class ActionSelectNextWaypoint :public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


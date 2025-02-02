#pragma once
#include "IBehaviorNode.h"
class Enemy;
//振り向くためのターンをするクラス
class ActionPrepareTurn : public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


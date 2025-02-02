#pragma once
#include "IBehaviorNode.h"
class Enemy;
//ターンを実行する動作クラス
class ActionPerformTurn :public IBehaviorNode
{public:
    bool Execute(Enemy* enemy) override;
};


#pragma once
#include "IBehaviorNode.h"
class Enemy;
//状態に合わせた変更を行うクラス
class ActionCheck:public IBehaviorNode
{public:
	bool Execute(Enemy* enemy) override;
};


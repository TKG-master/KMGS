#pragma once
#include "IBehaviorNode.h"
class Enemy;
//��Ԃɍ��킹���ύX���s���N���X
class ActionCheck:public IBehaviorNode
{public:
	bool Execute(Enemy* enemy) override;
};


#pragma once
#include "IBehaviorNode.h"
#include "Enemy.h"

class CheckPlayerInSight : public IBehaviorNode {
public:
    bool Execute(Enemy* enemy) override;

};


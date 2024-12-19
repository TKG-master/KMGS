#pragma once
#include "IBehaviorNode.h"
#include "Selector.h"
#include "Sequence.h"
#include "ActionMoveToPlayer.h"
#include "CheckPlayerInSight.h"
#include "ActionTurn.h"
#include "ActionLookaround.h"

class Enemy;

class EnemyAI {
private:
    IBehaviorNode* rootNode;

public:
    EnemyAI();
    void Update(Enemy* enemy);  // AIÇÃçXêV
    ~EnemyAI();

    IBehaviorNode* GetrootNode() { return rootNode; };

};


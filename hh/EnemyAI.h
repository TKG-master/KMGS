#pragma once
#include "IBehaviorNode.h"
#include "Selector.h"
#include "Sequence.h"
#include "ActionMoveToPlayer.h"
#include "CheckPlayerInSight.h"
#include "ActionTurn.h"
#include "ActionLookaround.h"
#include "ActionMoveSearch.h"
#include "ActionMoveback.h"

class Enemy;

class EnemyAI {
private:
    IBehaviorNode* rootNode;

    Selector* root;

    Sequence* patrolSequence;

    Sequence* TurnSequence;

    Sequence* LookaroundSequence;

public:
    EnemyAI();
    void Update(Enemy* enemy);  // AIÇÃçXêV
    ~EnemyAI();

    IBehaviorNode* GetrootNode() { return rootNode; };

};


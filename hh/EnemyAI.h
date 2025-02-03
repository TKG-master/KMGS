#pragma once
#include "IBehaviorNode.h"
#include "Selector.h"
#include "Sequence.h"
#include "StateSelector.h"
#include "ActionTurn.h"
#include "ActionSelectNextWaypoint.h"
#include "ActionMoveToWaypoint.h"
#include "ActionCheckArrival.h"
#include "ActionLookaround.h"
#include "ActionPerformTurn.h"
#include "ActionWait.h"
#include "ActionSerchMove.h"
#include "ActionCheck.h"
#include "ActionBookRead.h"
#include "ActionCheckState.h"
#include "ActionCheckTurn.h"
#include "ActionTurnTo.h"

class Enemy;

class EnemyAI {
private:

    EStateType currentState;

    IBehaviorNode* rootNode;

    Selector* stateSelector;

    Sequence* patrolSequence;

    Sequence* TurnSequence;

    Sequence* SerchSequence;

    Sequence* BookconnectionSequence;

    Sequence* BookReadSequence;

    Sequence* LookaroundSequence;

    Sequence* FixedSequence;

    Sequence* FixedLeftSequence;

    int Typenum = 0;

public:
    EnemyAI(int num);
    void Update(Enemy* enemy);  // AIの更新
    ~EnemyAI();

    void SetState(EStateType state);  // Enemy から状態変更通知


    IBehaviorNode* GetrootNode() { return rootNode; };

};


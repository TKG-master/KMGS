#pragma once
#include "IBehaviorNode.h"
#include "Selector.h"
#include "Sequence.h"
#include "StateSelector.h"
#include "ActionTurn.h"
#include "ActionPerformTurn.h"
#include "ActionWait.h"
#include "ActionPathMove.h"
#include "ActionCheck.h"
#include "ActionBookRead.h"
#include "ActionCheckState.h"
#include "ActionCheckTurn.h"
#include "ActionTurnTo.h"


#include "patrolSequence.h"
#include "FixedSequence.h"
#include "FixedLeftSequence.h"
#include "TurnSequence.h"
#include "SerchSequence.h"
#include "BackSequence.h"
#include "BookconnectionSequence.h"
#include "BookReadSequence.h"


class Enemy;

class EnemyAI {
private:

    EStateType currentState;

    IBehaviorNode* rootNode;

    Selector* stateSelector;

    Sequence* PatrolSequence;

    Sequence* turnSequence;

    Sequence* serchSequence;

    Sequence* backSequence;

    Sequence* bookconnectionSequence;

    Sequence* bookReadSequence;

    Sequence* fixedSequence;

    Sequence* fixedLeftSequence;

    int Typenum = 0;

public:
    EnemyAI(int num);
    void Update(Enemy* enemy);  // AIの更新
    ~EnemyAI();

    void SetState(EStateType state);  // Enemy から状態変更通知


    IBehaviorNode* GetrootNode() { return rootNode; };

};


#pragma once
#include "IBehaviorNode.h"
#include "Selector.h"
#include "Sequence.h"
#include "StateSelector.h"
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
    void Update(Enemy* enemy);  // AIÇÃçXêV
    ~EnemyAI();


    IBehaviorNode* GetrootNode() { return rootNode; };

};


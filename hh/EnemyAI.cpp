#include "EnemyAI.h"
#include "Enemy.h"


EnemyAI::EnemyAI(int num) {
    // ビヘイビアツリーの構築
    Selector* root = new Selector();

    Typenum = num;

    if (num != 100)
    {
        // **StateSelector** を作成
        stateSelector = new Selector();

        // **パトロールのシーケンス**
        Sequence* patrolSequence = new Sequence();
        patrolSequence->AddChild(new ActionCheckState(EStateType::Patrolling));
        patrolSequence->AddChild(new ActionSelectNextWaypoint());
        patrolSequence->AddChild(new ActionMoveToWaypoint());
        patrolSequence->AddChild(new ActionCheckArrival());
        patrolSequence->AddChild(new ActionLookaround());
        stateSelector->AddChild(patrolSequence);

        // **振り向きのシーケンス**
        Sequence* TurnSequence = new Sequence();
        TurnSequence->AddChild(new ActionCheckState(EStateType::Turn));
        TurnSequence->AddChild(new ActionPerformTurn());
        stateSelector->AddChild(TurnSequence);

        // **探しに行くシーケンス**
        Sequence* SerchSequence = new Sequence();
        SerchSequence->AddChild(new ActionCheckState(EStateType::Serch));
        SerchSequence->AddChild(new ActionWait());
        SerchSequence->AddChild(new ActionCheck());
        SerchSequence->AddChild(new ActionPathMove());
        stateSelector->AddChild(SerchSequence);

        // **持ち場に戻るシーケンス**
        Sequence* BackSequence = new Sequence();
        BackSequence->AddChild(new ActionCheckState(EStateType::Back));
        BackSequence->AddChild(new ActionWait());
        BackSequence->AddChild(new ActionCheck());
        BackSequence->AddChild(new ActionPathMove());
        stateSelector->AddChild(BackSequence);

        // **本のところまで移動するシーケンス**
        Sequence* BookconnectionSequence = new Sequence();
        BookconnectionSequence->AddChild(new ActionCheckState(EStateType::Bookconnection));
        BookconnectionSequence->AddChild(new ActionWait());
        BookconnectionSequence->AddChild(new ActionCheck());
        BookconnectionSequence->AddChild(new ActionPathMove());
        stateSelector->AddChild(BookconnectionSequence);

        // **本を読む動作**
        Sequence* BookReadSequence = new Sequence();
        BookReadSequence->AddChild(new ActionCheckState(EStateType::BookRead));
        BookReadSequence->AddChild(new ActionBookRead());
        stateSelector->AddChild(BookReadSequence);


        root->AddChild(stateSelector);
    }

    if (num == 100)
    {
        // **StateSelector** を作成
        stateSelector = new Selector();

        FixedSequence = new Sequence();
        FixedSequence->AddChild(new ActionCheckState(EStateType::Fixed));
        FixedSequence->AddChild(new ActionWait());
        FixedSequence->AddChild(new ActionTurnTo(0));
        FixedSequence->AddChild(new ActionCheckTurn());
        stateSelector->AddChild(FixedSequence);

        FixedLeftSequence = new Sequence();
        FixedLeftSequence->AddChild(new ActionCheckState(EStateType::FixedLeft));
        FixedLeftSequence->AddChild(new ActionWait());
        FixedLeftSequence->AddChild(new ActionTurnTo(1));
        FixedLeftSequence->AddChild(new ActionCheckTurn());
        stateSelector->AddChild(FixedLeftSequence);


        // **探しに行くシーケンス**
        Sequence* SerchSequence = new Sequence();
        SerchSequence->AddChild(new ActionCheckState(EStateType::Serch));
        SerchSequence->AddChild(new ActionWait());
        SerchSequence->AddChild(new ActionCheck());
        SerchSequence->AddChild(new ActionPathMove());
        stateSelector->AddChild(SerchSequence);

        // **持ち場に戻るシーケンス**
        Sequence* BackSequence = new Sequence();
        BackSequence->AddChild(new ActionCheckState(EStateType::Back));
        BackSequence->AddChild(new ActionWait());
        BackSequence->AddChild(new ActionCheck());
        BackSequence->AddChild(new ActionPathMove());
        stateSelector->AddChild(BackSequence);

        // **本のところまで移動するシーケンス**
        Sequence* BookconnectionSequence = new Sequence();
        BookconnectionSequence->AddChild(new ActionCheckState(EStateType::Bookconnection));
        BookconnectionSequence->AddChild(new ActionWait());
        BookconnectionSequence->AddChild(new ActionCheck());
        BookconnectionSequence->AddChild(new ActionPathMove());
        stateSelector->AddChild(BookconnectionSequence);

        // **本を読む動作**
        Sequence* BookReadSequence = new Sequence();
        BookReadSequence->AddChild(new ActionCheckState(EStateType::BookRead));
        BookReadSequence->AddChild(new ActionBookRead());
        stateSelector->AddChild(BookReadSequence);

        root->AddChild(stateSelector);
    }

    rootNode = root;
}

// ビヘイビアツリーの更新
void EnemyAI::Update(Enemy* enemy) {
    rootNode->Execute(enemy);
}


void EnemyAI::SetState(EStateType state)
{
    if (currentState != state) {
        currentState = state;
    }
}

// メモリの解放
EnemyAI::~EnemyAI() {

    delete rootNode;

}
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




        ////パトロール
        //patrolSelector = new Sequence();
        //patrolSelector->AddChild(new ActionRead());
        //patrolSelector->AddChild(new ActionBookRook());
        //patrolSelector->AddChild(new ActionMoveSearch());
        //patrolSelector->AddChild(new ActionMoveback());
        //patrolSelector->AddChild(new ActionMoveToPlayer());
        //root->AddChild(patrolSelector);
        ////ターン
        //TurnSequence = new Sequence();
        //TurnSequence->AddChild(new ActionTurn());
        //root->AddChild(TurnSequence);
        ////止まる
        //LookaroundSequence = new Sequence();
        //LookaroundSequence->AddChild(new ActionLookaround());
        //root->AddChild(LookaroundSequence);
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


        //警備
        //FixedSelector = new Selector();
        //FixedSelector->AddChild(new ActionRead());
        //FixedSelector->AddChild(new ActionBookRook());
        //FixedSelector->AddChild(new ActionMoveSearch());
        //FixedSelector->AddChild(new ActionMoveback());
        //FixedSelector->AddChild(new ActionConcern());
        //root->AddChild(FixedSelector);
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

void EnemyAI::BuildBehaviorTree()
{
    //delete rootNode;  // 古いツリーを削除
    //Selector* root = new Selector();

    //switch (currentState) {
    //case EStateType::Patrolling:
    //    patrolSequence = new Sequence();
    //    // パトロールシーケンスを作成
    //    patrolSequence = new Sequence();
    //    // 次の目的地を決定
    //    patrolSequence->AddChild(new ActionSelectNextWaypoint());
    //    // 目的地へ移動
    //    patrolSequence->AddChild(new ActionMoveToWaypoint());
    //    // 目的地到達チェック
    //    patrolSequence->AddChild(new ActionCheckArrival());
    //    // 到達したら見回す
    //    patrolSequence->AddChild(new ActionLookaround());
    //    // ルートノードに追加
    //    root->AddChild(patrolSequence);
    //    break;
    //case EStateType::Turn:
    //    TurnSequence = new Sequence();
    //    TurnSequence->AddChild(new ActionPerformTurn());
    //    root->AddChild(TurnSequence);
    //    break;

    //case EStateType::BookRead:
    //    BookReadSequence = new Sequence();

    //    root->AddChild(BookReadSequence);
    //    break;

    //case EStateType::RookBook:
    //    RookBookSequence = new Sequence();

    //    root->AddChild(RookBookSequence);
        //break;
    
}

// メモリの解放
EnemyAI::~EnemyAI() {

    delete rootNode;

}
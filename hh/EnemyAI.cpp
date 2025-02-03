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

        //ビヘイビアツリーの作成
        PatrolSequence          = new patrolSequence();
        turnSequence            = new TurnSequence();
        serchSequence           = new SerchSequence();
        backSequence            = new BackSequence();
        bookconnectionSequence  = new BookconnectionSequence();
        bookReadSequence        = new BookReadSequence();


        stateSelector->AddChild(PatrolSequence);
        stateSelector->AddChild(turnSequence);
        stateSelector->AddChild(serchSequence);
        stateSelector->AddChild(backSequence);
        stateSelector->AddChild(bookconnectionSequence);
        stateSelector->AddChild(bookReadSequence);

        root->AddChild(stateSelector);
    }

    if (num == 100)
    {
        // **StateSelector** を作成
        stateSelector = new Selector();

        //ビヘイビアツリーの作成
        fixedSequence           = new FixedSequence();
        fixedLeftSequence       = new FixedLeftSequence();
        serchSequence           = new SerchSequence();
        backSequence            = new BackSequence();
        bookconnectionSequence  = new BookconnectionSequence();
        bookReadSequence        = new BookReadSequence();
        //セレクターに動作のシーケンスを追加
        stateSelector->AddChild(fixedSequence);
        stateSelector->AddChild(fixedLeftSequence);
        stateSelector->AddChild(serchSequence);
        stateSelector->AddChild(backSequence);
        stateSelector->AddChild(bookconnectionSequence);
        stateSelector->AddChild(bookReadSequence);

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
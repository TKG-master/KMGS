#include "EnemyAI.h"
#include "Enemy.h"

EnemyAI::EnemyAI() {
    // ビヘイビアツリーの構築

    //パトロール
    Selector* root = new Selector();
    Sequence* patrolSequence = new Sequence();
    patrolSequence->AddChild(new ActionMoveToPlayer());
    root->AddChild(patrolSequence);
    rootNode = root;
    //ターン
    Sequence* TurnSequence = new Sequence();
    TurnSequence->AddChild(new ActionTurn());
    root->AddChild(TurnSequence);
    //止まる
    Sequence* LookaroundSequence = new Sequence();
    LookaroundSequence->AddChild(new ActionLookaround());
    root->AddChild(LookaroundSequence);

}

void EnemyAI::Update(Enemy* enemy) {
    rootNode->Execute(enemy);  // ビヘイビアツリーの更新
}

EnemyAI::~EnemyAI() {
    delete rootNode;  // メモリの解放
}
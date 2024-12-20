#include "EnemyAI.h"
#include "Enemy.h"

EnemyAI::EnemyAI() {
    // ビヘイビアツリーの構築

    //パトロール
    root = new Selector();
    patrolSequence = new Sequence();
    patrolSequence->AddChild(new ActionMoveToPlayer());
    patrolSequence->AddChild(new ActionMoveSearch());
    patrolSequence->AddChild(new ActionMoveback());
    root->AddChild(patrolSequence);
    rootNode = root;
    //ターン
    TurnSequence = new Sequence();
    TurnSequence->AddChild(new ActionTurn());
    root->AddChild(TurnSequence);
    //止まる
    LookaroundSequence = new Sequence();
    LookaroundSequence->AddChild(new ActionLookaround());
    root->AddChild(LookaroundSequence);

}

void EnemyAI::Update(Enemy* enemy) {
    rootNode->Execute(enemy);  // ビヘイビアツリーの更新
}

EnemyAI::~EnemyAI() {
    delete rootNode;  // メモリの解放

    patrolSequence->UnInit();
    delete patrolSequence;
    TurnSequence->UnInit();
    delete TurnSequence;
    LookaroundSequence->UnInit();
    delete LookaroundSequence;

}
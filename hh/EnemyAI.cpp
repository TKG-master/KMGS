#include "EnemyAI.h"
#include "Enemy.h"

EnemyAI::EnemyAI() {
    // ビヘイビアツリーの構築

    //パトロール
    Selector* root = new Selector();
    patrolSelector = new Selector();
    patrolSelector->AddChild(new ActionMoveToPlayer());
    patrolSelector->AddChild(new ActionMoveSearch());
    patrolSelector->AddChild(new ActionMoveback());
    root->AddChild(patrolSelector);
    rootNode = root;
    //ターン
    TurnSequence = new Sequence();
    TurnSequence->AddChild(new ActionTurn());
    root->AddChild(TurnSequence);
    //止まる
    LookaroundSequence = new Sequence();
    LookaroundSequence->AddChild(new ActionLookaround());
    root->AddChild(LookaroundSequence);
    //Fixed
    FixedSelector = new Selector();
    FixedSelector->AddChild(new ActionConcern());
    root->AddChild(FixedSelector);

}

// ビヘイビアツリーの更新
void EnemyAI::Update(Enemy* enemy) {
    rootNode->Execute(enemy);
}
// メモリの解放
EnemyAI::~EnemyAI() {

    delete rootNode;

    //UnInitで木の葉ノードのメモリ解放
    patrolSelector->UnInit();
    delete patrolSelector;

    TurnSequence->UnInit();
    delete TurnSequence;

    LookaroundSequence->UnInit();
    delete LookaroundSequence;

    FixedSelector->UnInit();
    delete  FixedSelector;

}
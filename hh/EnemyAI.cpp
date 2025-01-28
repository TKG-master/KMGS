#include "EnemyAI.h"
#include "Enemy.h"

EnemyAI::EnemyAI() {
    // ビヘイビアツリーの構築

    
    Selector* root = new Selector();
    //パトロール
    patrolSelector = new Selector();
    patrolSelector->AddChild(new ActionRead());
    patrolSelector->AddChild(new ActionBookRook());
    patrolSelector->AddChild(new ActionMoveSearch());
    patrolSelector->AddChild(new ActionMoveback());
    patrolSelector->AddChild(new ActionMoveToPlayer());
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
    //警備
    FixedSelector = new Selector();
    FixedSelector->AddChild(new ActionRead());
    FixedSelector->AddChild(new ActionBookRook());
    FixedSelector->AddChild(new ActionMoveSearch());
    FixedSelector->AddChild(new ActionMoveback());
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
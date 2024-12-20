#include "EnemyAI.h"
#include "Enemy.h"

EnemyAI::EnemyAI() {
    // �r�w�C�r�A�c���[�̍\�z

    //�p�g���[��
    root = new Selector();
    patrolSequence = new Sequence();
    patrolSequence->AddChild(new ActionMoveToPlayer());
    patrolSequence->AddChild(new ActionMoveSearch());
    patrolSequence->AddChild(new ActionMoveback());
    root->AddChild(patrolSequence);
    rootNode = root;
    //�^�[��
    TurnSequence = new Sequence();
    TurnSequence->AddChild(new ActionTurn());
    root->AddChild(TurnSequence);
    //�~�܂�
    LookaroundSequence = new Sequence();
    LookaroundSequence->AddChild(new ActionLookaround());
    root->AddChild(LookaroundSequence);

}

void EnemyAI::Update(Enemy* enemy) {
    rootNode->Execute(enemy);  // �r�w�C�r�A�c���[�̍X�V
}

EnemyAI::~EnemyAI() {
    delete rootNode;  // �������̉��

    patrolSequence->UnInit();
    delete patrolSequence;
    TurnSequence->UnInit();
    delete TurnSequence;
    LookaroundSequence->UnInit();
    delete LookaroundSequence;

}
#include "EnemyAI.h"
#include "Enemy.h"

EnemyAI::EnemyAI() {
    // �r�w�C�r�A�c���[�̍\�z

    //�p�g���[��
    Selector* root = new Selector();
    Sequence* patrolSequence = new Sequence();
    patrolSequence->AddChild(new ActionMoveToPlayer());
    root->AddChild(patrolSequence);
    rootNode = root;
    //�^�[��
    Sequence* TurnSequence = new Sequence();
    TurnSequence->AddChild(new ActionTurn());
    root->AddChild(TurnSequence);
    //�~�܂�
    Sequence* LookaroundSequence = new Sequence();
    LookaroundSequence->AddChild(new ActionLookaround());
    root->AddChild(LookaroundSequence);

}

void EnemyAI::Update(Enemy* enemy) {
    rootNode->Execute(enemy);  // �r�w�C�r�A�c���[�̍X�V
}

EnemyAI::~EnemyAI() {
    delete rootNode;  // �������̉��
}
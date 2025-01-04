#include "EnemyAI.h"
#include "Enemy.h"

EnemyAI::EnemyAI() {
    // �r�w�C�r�A�c���[�̍\�z

    //�p�g���[��
    Selector* root = new Selector();
    patrolSelector = new Selector();
    patrolSelector->AddChild(new ActionRead());
    patrolSelector->AddChild(new ActionBookRook());
    patrolSelector->AddChild(new ActionMoveToPlayer());
    patrolSelector->AddChild(new ActionMoveSearch());
    patrolSelector->AddChild(new ActionMoveback());
    root->AddChild(patrolSelector);
    rootNode = root;
    //�^�[��
    TurnSequence = new Sequence();
    TurnSequence->AddChild(new ActionTurn());
    root->AddChild(TurnSequence);
    //�~�܂�
    LookaroundSequence = new Sequence();
    LookaroundSequence->AddChild(new ActionLookaround());
    root->AddChild(LookaroundSequence);
    //Fixed
    FixedSelector = new Selector();
    FixedSelector->AddChild(new ActionConcern());
    FixedSelector->AddChild(new ActionRead());
    FixedSelector->AddChild(new ActionBookRook());
    FixedSelector->AddChild(new ActionMoveSearch());
    FixedSelector->AddChild(new ActionMoveback());
    root->AddChild(FixedSelector);
}

// �r�w�C�r�A�c���[�̍X�V
void EnemyAI::Update(Enemy* enemy) {
    rootNode->Execute(enemy);
}
// �������̉��
EnemyAI::~EnemyAI() {

    delete rootNode;

    //UnInit�Ŗ؂̗t�m�[�h�̃��������
    patrolSelector->UnInit();
    delete patrolSelector;

    TurnSequence->UnInit();
    delete TurnSequence;

    LookaroundSequence->UnInit();
    delete LookaroundSequence;

    FixedSelector->UnInit();
    delete  FixedSelector;

}
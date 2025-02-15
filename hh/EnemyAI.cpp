#include "EnemyAI.h"
#include "Enemy.h"


EnemyAI::EnemyAI(int num) {
    // �r�w�C�r�A�c���[�̍\�z
    Selector* root = new Selector();

    Typenum = num;

    if (num != 100)
    {
        // **StateSelector** ���쐬
        stateSelector = new Selector();

        //�r�w�C�r�A�c���[�̍쐬
        PatrolSequence          = new patrolSequence();
        turnSequence            = new TurnSequence();
        serchSequence           = new SerchSequence();
        backSequence            = new BackSequence();
        bookconnectionSequence  = new BookconnectionSequence();
        bookReadSequence        = new BookReadSequence();


        stateSelector->AddChild(bookconnectionSequence);
        stateSelector->AddChild(bookReadSequence);
        stateSelector->AddChild(PatrolSequence);
        stateSelector->AddChild(turnSequence);
        stateSelector->AddChild(serchSequence);
        stateSelector->AddChild(backSequence);

        root->AddChild(stateSelector);
    }

    if (num == 100)
    {
        // **StateSelector** ���쐬
        stateSelector = new Selector();

        //�r�w�C�r�A�c���[�̍쐬
        fixedSequence           = new FixedSequence();
        fixedLeftSequence       = new FixedLeftSequence();
        serchSequence           = new SerchSequence();
        backSequence            = new BackSequence();
        bookconnectionSequence  = new BookconnectionSequence();
        bookReadSequence        = new BookReadSequence();
        //�Z���N�^�[�ɓ���̃V�[�P���X��ǉ�
        stateSelector->AddChild(bookconnectionSequence);
        stateSelector->AddChild(bookReadSequence);
        stateSelector->AddChild(fixedSequence);
        stateSelector->AddChild(fixedLeftSequence);
        stateSelector->AddChild(serchSequence);
        stateSelector->AddChild(backSequence);

        root->AddChild(stateSelector);
    }

    rootNode = root;
}

// �r�w�C�r�A�c���[�̍X�V
void EnemyAI::Update(Enemy* enemy) {
    rootNode->Execute(enemy);
}

// �������̉��
EnemyAI::~EnemyAI() {

    delete rootNode;

}
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

        // **�p�g���[���̃V�[�P���X**
        Sequence* patrolSequence = new Sequence();
        patrolSequence->AddChild(new ActionCheckState(EStateType::Patrolling));
        patrolSequence->AddChild(new ActionSelectNextWaypoint());
        patrolSequence->AddChild(new ActionMoveToWaypoint());
        patrolSequence->AddChild(new ActionCheckArrival());
        patrolSequence->AddChild(new ActionLookaround());
        stateSelector->AddChild(patrolSequence);

        // **�U������̃V�[�P���X**
        Sequence* TurnSequence = new Sequence();
        TurnSequence->AddChild(new ActionCheckState(EStateType::Turn));
        TurnSequence->AddChild(new ActionPerformTurn());
        stateSelector->AddChild(TurnSequence);

        // **�T���ɍs���V�[�P���X**
        Sequence* SerchSequence = new Sequence();
        SerchSequence->AddChild(new ActionCheckState(EStateType::Serch));
        SerchSequence->AddChild(new ActionWait());
        SerchSequence->AddChild(new ActionCheck());
        SerchSequence->AddChild(new ActionPathMove());
        stateSelector->AddChild(SerchSequence);

        // **������ɖ߂�V�[�P���X**
        Sequence* BackSequence = new Sequence();
        BackSequence->AddChild(new ActionCheckState(EStateType::Back));
        BackSequence->AddChild(new ActionWait());
        BackSequence->AddChild(new ActionCheck());
        BackSequence->AddChild(new ActionPathMove());
        stateSelector->AddChild(BackSequence);

        // **�{�̂Ƃ���܂ňړ�����V�[�P���X**
        Sequence* BookconnectionSequence = new Sequence();
        BookconnectionSequence->AddChild(new ActionCheckState(EStateType::Bookconnection));
        BookconnectionSequence->AddChild(new ActionWait());
        BookconnectionSequence->AddChild(new ActionCheck());
        BookconnectionSequence->AddChild(new ActionPathMove());
        stateSelector->AddChild(BookconnectionSequence);

        // **�{��ǂޓ���**
        Sequence* BookReadSequence = new Sequence();
        BookReadSequence->AddChild(new ActionCheckState(EStateType::BookRead));
        BookReadSequence->AddChild(new ActionBookRead());
        stateSelector->AddChild(BookReadSequence);


        root->AddChild(stateSelector);




        ////�p�g���[��
        //patrolSelector = new Sequence();
        //patrolSelector->AddChild(new ActionRead());
        //patrolSelector->AddChild(new ActionBookRook());
        //patrolSelector->AddChild(new ActionMoveSearch());
        //patrolSelector->AddChild(new ActionMoveback());
        //patrolSelector->AddChild(new ActionMoveToPlayer());
        //root->AddChild(patrolSelector);
        ////�^�[��
        //TurnSequence = new Sequence();
        //TurnSequence->AddChild(new ActionTurn());
        //root->AddChild(TurnSequence);
        ////�~�܂�
        //LookaroundSequence = new Sequence();
        //LookaroundSequence->AddChild(new ActionLookaround());
        //root->AddChild(LookaroundSequence);
    }

    if (num == 100)
    {
        // **StateSelector** ���쐬
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


        // **�T���ɍs���V�[�P���X**
        Sequence* SerchSequence = new Sequence();
        SerchSequence->AddChild(new ActionCheckState(EStateType::Serch));
        SerchSequence->AddChild(new ActionWait());
        SerchSequence->AddChild(new ActionCheck());
        SerchSequence->AddChild(new ActionPathMove());
        stateSelector->AddChild(SerchSequence);

        // **������ɖ߂�V�[�P���X**
        Sequence* BackSequence = new Sequence();
        BackSequence->AddChild(new ActionCheckState(EStateType::Back));
        BackSequence->AddChild(new ActionWait());
        BackSequence->AddChild(new ActionCheck());
        BackSequence->AddChild(new ActionPathMove());
        stateSelector->AddChild(BackSequence);

        // **�{�̂Ƃ���܂ňړ�����V�[�P���X**
        Sequence* BookconnectionSequence = new Sequence();
        BookconnectionSequence->AddChild(new ActionCheckState(EStateType::Bookconnection));
        BookconnectionSequence->AddChild(new ActionWait());
        BookconnectionSequence->AddChild(new ActionCheck());
        BookconnectionSequence->AddChild(new ActionPathMove());
        stateSelector->AddChild(BookconnectionSequence);

        // **�{��ǂޓ���**
        Sequence* BookReadSequence = new Sequence();
        BookReadSequence->AddChild(new ActionCheckState(EStateType::BookRead));
        BookReadSequence->AddChild(new ActionBookRead());
        stateSelector->AddChild(BookReadSequence);

        root->AddChild(stateSelector);


        //�x��
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

// �r�w�C�r�A�c���[�̍X�V
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
    //delete rootNode;  // �Â��c���[���폜
    //Selector* root = new Selector();

    //switch (currentState) {
    //case EStateType::Patrolling:
    //    patrolSequence = new Sequence();
    //    // �p�g���[���V�[�P���X���쐬
    //    patrolSequence = new Sequence();
    //    // ���̖ړI�n������
    //    patrolSequence->AddChild(new ActionSelectNextWaypoint());
    //    // �ړI�n�ֈړ�
    //    patrolSequence->AddChild(new ActionMoveToWaypoint());
    //    // �ړI�n���B�`�F�b�N
    //    patrolSequence->AddChild(new ActionCheckArrival());
    //    // ���B�����猩��
    //    patrolSequence->AddChild(new ActionLookaround());
    //    // ���[�g�m�[�h�ɒǉ�
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

// �������̉��
EnemyAI::~EnemyAI() {

    delete rootNode;

}
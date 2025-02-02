#pragma once

enum ObjectType {
    PLAYER, //�v���C���[
    ENEMY, //�G
    BOX,   //�{�b�N�X
    PPLATE, //�����o�鏰
    Goal,   //�S�[��
    BOOK,
};

enum class EStateType {
    Patrolling,     //�p�j
    Fixed,          //�x���E����
    FixedLeft,      //�x��������
    Turn,            //�G�̌�����������
    Bookconnection, //�{��ǂނ܂�
    BookRead,       //�{��ǂ�ł�Ƃ�
    Serch,          //�T���ɗ���Ƃ�
    Back,
};

enum class PStateType {
    STAND,
    SNEAK,
    STIKY,
    STANDEYE,
    SNEAKEYE,
};

#pragma once

enum ObjectType {
    PLAYER, //�v���C���[
    ENEMY, //�G
    BOX,   //�{�b�N�X
    Goal,   //�S�[��
};

enum class EStateType {
    Patrolling,     //�p�j
    Lookaround,     //���������
    Turn,            //�G�̌�����߂�
    Fixed,
};

enum class PStateType {
    STAND,
    SNEAK,
    STANDEYE,
    SNEAKEYE,
};


enum class GameState {
    START,
    UPDATE,
    END,
};

enum class FadeState {
    NO_FADE,
    FADE_IN,
    FADE_OUT,
};

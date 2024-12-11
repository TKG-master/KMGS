#pragma once

enum ObjectType {
    PLAYER, //�v���C���[
    ENEMY, //�G
    BOX,   //�{�b�N�X
    Goal,   //�S�[��
};

enum class EStateType {
    Patrolling,  // �p�j
    Alerted,     // �v���C���[��������
    Investigating // ���Ԓn�_�̃t�F�[�Y�i��F�v���C���[������������̒T���j
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

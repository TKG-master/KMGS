#pragma once
#include "Input.h"
#include "Character.h"


class Player : public Character
{
private:
    //�x�N�g���̌���
    DirectX::SimpleMath::Vector3 Velocity;

    //�}�b�v�̏����i�[
    std::vector<std::vector<int>> Mdata;

    //�ړ����x
    float MoveSpeed = 1.0f;
    //�������Ԃ��H
    bool Moveflg;

    bool Stand = true;

    // �O�t���[�����ꂽ�Փ˕␳�̕���
    CORRECT_DIR prevFrameCorrect = { 0 };
    //�{�b�N�X�ɓ������Ă鎞�̔���
    bool hitBox = false;

    bool sticking = false;

    //�v���C���[�������o�����Ƃ���bool�^
    bool knockSound = false;

    //Update���F�ړ�����
    void MoveUpdate();




public:
    void Init(std::string ModelName, std::string TexFolderPath,
        std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader);

    Player(std::string ModelName, std::string TexFolderPath,
        std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader);
    ~Player();

    void UnInit();
    void Update();
    void Draw();
    void AnimUpdate() {Character::Update();};

    void SetSpeed(float ac) { MoveSpeed = ac; };
    float GetSpeed() { return MoveSpeed; };

    void squareUpdate(){	//�����蔻��̈ʒu���X�V
    this->m_AnimationObject.m_Position.x = this->square.centerX;
    this->m_AnimationObject.m_Position.y = this->square.centerY;
    this->m_AnimationObject.m_Position.z = this->square.centerZ;
    }

    void SetMapdata(std::vector<std::vector<int>> data) { this->Mdata = data; };
    void SetknockSound(bool flg) { this->knockSound = flg; };
    bool GetKnockSound() { return this->knockSound; };

    void SetGoalState() { 
        STATUS = GOAL;
        this->SetToAnimationName("Goal"); };

    bool GetSticking() { return this->sticking; };
    void SetSticking(bool flg) { this->sticking = flg; };

    //�ǂɒ���t���Ă���Ƃ��̌��������킹��
    void StickyWall(CORRECT_DIR dir);

    CORRECT_DIR Getdir() { return this->prevFrameCorrect; };

    SQUARE3D Getsquare() { return this->square; };



};


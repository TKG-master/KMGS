#pragma once
#include "Input.h"
#include "Character.h"
#include "Book.h"


class Player : public Character
{
private:
    //�x�N�g���̌���
    DirectX::SimpleMath::Vector3 Velocity;

    Book* book;

    //�}�b�v�̏����i�[
    std::vector<std::vector<int>> Mdata;

    //�ړ����x
    float MoveSpeed = 1.0f;
    //�������Ԃ��H
    bool Moveflg;

    bool Bookput = false;

    bool Stand = true;

    bool FPSeye = false;

    bool Sticky = false;

    PStateType State = PStateType::STAND;

    // �O�t���[�����ꂽ�Փ˕␳�̕���
    CORRECT_DIR prevFrameCorrect = { 0 };
    //�{�b�N�X�ɓ������Ă鎞�̔���
    bool hitBox = false;

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

    bool GetFPSeye() { return this->FPSeye; };
    void SetFPSeye(bool flg) { this->FPSeye = flg; };
    //����
    void PlayerInput();
    //�ړ�����
    void moveprocess();
    //�����Ȃǂ𐮂���
    void VelocityS();

    void SetGoalState() { 
        STATUS = GOAL;
        this->SetToAnimationName("Goal"); };

    PStateType GetState() { return this->State; };
    void SetState(PStateType state) { this->State = state; };

    DirectX::SimpleMath::Vector3 GetFacingDirection();

    //�ǂɒ���t���Ă���Ƃ��̌��������킹��
    void StickyWall(CORRECT_DIR dir);

    bool GetSticky() { return this->Sticky; };
    void SetSticky(bool flg) { this->Sticky = flg; };

    CORRECT_DIR Getdir() { return this->prevFrameCorrect; };

    SQUARE3D Getsquare() { return this->square; };



};


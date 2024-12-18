#pragma once
#include "Input.h"
#include "Character.h"


class Player : public Character
{
private:
    //ベクトルの向き
    DirectX::SimpleMath::Vector3 Velocity;

    //マップの情報を格納
    std::vector<std::vector<int>> Mdata;

    //移動速度
    float MoveSpeed = 1.0f;
    //動ける状態か？
    bool Moveflg;

    bool Stand = true;

    bool FPSeye = false;

    PStateType State = PStateType::STAND;

    // 前フレームされた衝突補正の方向
    CORRECT_DIR prevFrameCorrect = { 0 };
    //ボックスに当たってる時の判定
    bool hitBox = false;

    //プレイヤーが音を出したときのbool型
    bool knockSound = false;

    //Update内：移動処理
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

    void squareUpdate(){	//当たり判定の位置を更新
    this->m_AnimationObject.m_Position.x = this->square.centerX;
    this->m_AnimationObject.m_Position.y = this->square.centerY;
    this->m_AnimationObject.m_Position.z = this->square.centerZ;
    }

    void SetMapdata(std::vector<std::vector<int>> data) { this->Mdata = data; };
    void SetknockSound(bool flg) { this->knockSound = flg; };
    bool GetKnockSound() { return this->knockSound; };

    bool GetFPSeye() { return this->FPSeye; };
    void SetFPSeye(bool flg) { this->FPSeye = flg; };

    void PlayerInput();

    void SetGoalState() { 
        STATUS = GOAL;
        this->SetToAnimationName("Goal"); };

    PStateType GetState() { return this->State; };
    void SetState(PStateType state) { this->State = state; };

    DirectX::SimpleMath::Vector3 GetFacingDirection();

    //壁に張り付いているときの向きを合わせる
    void StickyWall(CORRECT_DIR dir);

    CORRECT_DIR Getdir() { return this->prevFrameCorrect; };

    SQUARE3D Getsquare() { return this->square; };



};


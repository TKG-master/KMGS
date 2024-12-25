#pragma once
#include "CShader.h"
#include "CAnimationData.h"
#include "CAnimationMesh.h"
#include "CAnimationObject.h"
#include "CCollision.h"

#include"Structs.h"

enum CharacterStatus
{
    NONE,       //何もなし
    IDLE,       //待機中
    WALK,       //歩き中
    STIKY,      //張り付き中
    SIDESTEPLEFT,   //横歩き左
    SIDESTEPLIGHY,  //横歩き右
    SNEAK,      //しゃがみ
    GOAL,       //ゴールした時
    SNEAKWLKE,   //しゃがみ歩き
    RUN,        //走行中
};

class Character
{
protected:
    //===== 3Dモデル構成要素 =====

    // シェーダー
    CShader	m_Shader;
    // アニメーションメッシュ
    CAnimationMesh m_AnimationMesh;
    // アニメーションオブジェクト
    CAnimationObject m_AnimationObject;
    // アニメーションデータ
    std::unordered_map<std::string, CAnimationData> m_AnimationData;
    // ブレンドレート
    float m_BlendRate = 0.0f;

    //===== 更新処理に使用 =====

    bool AnimEndState = false;

    // アニメーション速度
    float m_AnimationSpeed = 1.0f;
    //アニメーションブレンド速度
    float m_AnimationBrendSpeed = 0.05f;

    // 現在のアニメーション名
    std::string m_FromAnimationName;
    // 次のアニメーション名
    std::string m_ToAnimationName;
    // アニメーションをブレンド＆変更させる、完了でtrue出力
    bool AnimationBrend();

    CharacterStatus STATUS = NONE;

    DirectX::SimpleMath::Vector3 CollisionScale = { 25.0f,0.0f,25.0f };


public:

    SQUARE3D square = { 0.0f,0.0f,0.0f , 0.0f,0.0f,0.0f };

    // 1:モデルファイル、2:テクスチャファイル、3:モーションファイル、4,5:V&Pシェーダー
    // MotionNameにはvector<MotionStruct>を作成し引数に。
    virtual void Init(
        std::string ModelName, std::string TexFolderPath,
        std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader);

    virtual void EnemyInit(
        CAnimationMesh m_AnimationMesh,
        std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader);



    virtual void UnInit();
    virtual void Update();
    virtual void Draw();

    CharacterStatus GetAstatus() { return this->STATUS; };
    void SetAstatus(CharacterStatus status) { this->STATUS = status; };

    void SetAnimationSpeed(float as) { m_AnimationSpeed = as; }
    float GetAnimationSpeed() { return m_AnimationSpeed; }

    //次に使用したいアニメーションの名前(キー)を格納
    void SetToAnimationName(std::string n) { m_ToAnimationName = n; }


    DirectX::SimpleMath::Vector3 GetPosition() const{ return m_AnimationObject.m_Position; };
    void SetPosition(DirectX::SimpleMath::Vector3 v) { m_AnimationObject.m_Position = v; }
    DirectX::SimpleMath::Vector3 GetRotation() { return m_AnimationObject.m_Rotation; };
    void SetRotation(DirectX::SimpleMath::Vector3 v) { m_AnimationObject.m_Rotation = v; }
    DirectX::SimpleMath::Vector3 GetScale() { return m_AnimationObject.m_Scale; };
    void SetScale(DirectX::SimpleMath::Vector3 v) { m_AnimationObject.m_Scale = v; }

    DirectX::SimpleMath::Vector3 GetCollisionScale() const { return CollisionScale; };

    void AddPositionX(float n) { m_AnimationObject.m_Position.x += n; };
    void AddPositionY(float n) { m_AnimationObject.m_Position.y += n; };
    void AddPositionZ(float n) { m_AnimationObject.m_Position.z += n; };

    //回転後に使用：角度の修正
    void ModifyRotation();

    SQUARE3D GetCollisionSize() { return this->square; };

    void Setsquare3D(SQUARE3D S) {
        this->square.sizeX = S.sizeX;
        this->square.sizeY = S.sizeY;
        this->square.sizeZ = S.sizeZ;
    }

    void SetSquare3D(DirectX::SimpleMath::Vector3 v) {
        this->square.sizeX = v.x;
        this->square.sizeY = v.y;
        this->square.sizeZ = v.z;
    }


    void CollisionInit(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 size);

    void SetAnimEndState(bool flg) { this->AnimEndState = flg; };
    bool GetAnimEndState() { return this->AnimEndState; };


};


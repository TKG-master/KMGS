#pragma once
#include "CShader.h"
#include "CAnimationData.h"
#include "CAnimationMesh.h"
#include "CAnimationObject.h"
#include "CCollision.h"

#include"Structs.h"

enum CharacterStatus
{
    NONE,       //�����Ȃ�
    IDLE,       //�ҋ@��
    WALK,       //������
    STIKY,      //����t����
    SIDESTEPLEFT,   //��������
    SIDESTEPLIGHY,  //�������E
    SNEAK,      //���Ⴊ��
    GOAL,       //�S�[��������
    SNEAKWLKE,   //���Ⴊ�ݕ���
    RUN,        //���s��
};

class Character
{
protected:
    //===== 3D���f���\���v�f =====

    // �V�F�[�_�[
    CShader	m_Shader;
    // �A�j���[�V�������b�V��
    CAnimationMesh m_AnimationMesh;
    // �A�j���[�V�����I�u�W�F�N�g
    CAnimationObject m_AnimationObject;
    // �A�j���[�V�����f�[�^
    std::unordered_map<std::string, CAnimationData> m_AnimationData;
    // �u�����h���[�g
    float m_BlendRate = 0.0f;

    //===== �X�V�����Ɏg�p =====

    bool AnimEndState = false;

    // �A�j���[�V�������x
    float m_AnimationSpeed = 1.0f;
    //�A�j���[�V�����u�����h���x
    float m_AnimationBrendSpeed = 0.05f;

    // ���݂̃A�j���[�V������
    std::string m_FromAnimationName;
    // ���̃A�j���[�V������
    std::string m_ToAnimationName;
    // �A�j���[�V�������u�����h���ύX������A������true�o��
    bool AnimationBrend();

    CharacterStatus STATUS = NONE;

    DirectX::SimpleMath::Vector3 CollisionScale = { 25.0f,0.0f,25.0f };


public:

    SQUARE3D square = { 0.0f,0.0f,0.0f , 0.0f,0.0f,0.0f };

    // 1:���f���t�@�C���A2:�e�N�X�`���t�@�C���A3:���[�V�����t�@�C���A4,5:V&P�V�F�[�_�[
    // MotionName�ɂ�vector<MotionStruct>���쐬�������ɁB
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

    //���Ɏg�p�������A�j���[�V�����̖��O(�L�[)���i�[
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

    //��]��Ɏg�p�F�p�x�̏C��
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


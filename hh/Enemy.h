#pragma once
#include <SimpleMath.h>
#include "CShader.h"
#include "Character.h"
#include "Timer.h"
#include "EnemyAI.h"

class EnemyAI;

class GameUI;

class Player;

class Enemy : public Character
{
private:

	EnemyAI* AI;

	Timer* time;

	//�����Ă������
	DirectX::SimpleMath::Vector3 forward = { 0.0f,0.0f,-1.0f };
	//����͈͂̐F
	DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(1.0f, 0.0f, 0.0f, 0.8f);
	//��`�̓_�̏ꏊ
	DirectX::SimpleMath::Vector3 point;
	//���̒n�_
	DirectX::SimpleMath::Vector3 nextPosition;
	//�������x
	float MoveSpeed = 1.5f;
	//��ԏ��߂ɂ���ꏊ
	DirectX::SimpleMath::Vector3 StartPosition;
	//����͈͂�`�悷�邽�߂ɕK�v�ȍs��
	DirectX::SimpleMath::Matrix rotation;
	//���݂̏�Ԃ��ێ�����
	EStateType state = EStateType::Patrolling;
	// �o�H����ێ����郁���o�ϐ�
	std::vector<DirectX::SimpleMath::Vector3> path;
	int currentPathIndex = 0;
	//�p�j���郋�[�g�̃|�C���g�i�[�̔z��
	std::vector<DirectX::SimpleMath::Vector3> wandering_path;
	//�x������ꍇ�̌���
	std::vector<DirectX::SimpleMath::Vector3> forward_path;
	int currentwanderingpathIndex = 0;
	//���̜p�j�̖ړI�n
	DirectX::SimpleMath::Vector3 targetPos;
	// ���݂̈ʒu
	DirectX::SimpleMath::Vector3 currentPosition;
	//���Vector3
	DirectX::SimpleMath::Vector3 rayDirection;
	//���[�_�̂ǂ��Ɏ��������邩
	DirectX::SimpleMath::Vector2 RaderPos;


	float rayY = 80.0f;
	//���C���ǂ��܂ŐL�΂��ē���������
	float hitDis = 0.0f;

	int bookCount = 0;


	//���������������H
	bool hearSound = false;
	//�o�H�T������bool�^
	bool Search = false;
	//�A�
	bool back = false;
	//�߂܂���
	bool getcaught = false;
	//���n���Ă���Ƃ��̃u�[���^
	bool secrity = false;
	//�{������������bool�^
	bool RookBook = false;
	//�{�ɖ����ɂȂ��Ă���Ƃ�
	bool bookRead = false;
	//���[�_�̒��ɂ���̂��H
	bool RaderIn = false;



	float deltaTime = 0.005f;
	float Time1 = 0.5;
	float Time = 0.0f;

	//�v���C���[�̃f�[�^�[�i�ǂݎ��p�j
	const Player* playerdate;

	//��`��`�悷��Ƃ��̃Z�O�����g��
	static constexpr int numSegments = 50;
	std::vector<VERTEX_3D> fanVertices = std::vector<VERTEX_3D>(numSegments + 2);

	// ����p�̐ݒ�
	float viewAngle = 0.5f; // ����p
	float viewDistance = 300.0f; // ����̋���
	bool test = false;
	//����͈͂�`�悷��Ƃ��̔������p��float�^
	float viewX = 2.0f;
	float viewZ = 2.8f;
	//�����Ă�������̕ێ�
	DirectX::SimpleMath::Vector3 SaveForward;

	CIndexBuffer				e_IndexBuffer;
	CVertexBuffer<VERTEX_3D>	e_VertexBuffer;
	CMaterial					e_Material;
	CTexture					e_Texture;
	CShader						e_Shader;

public:

	DirectX::SimpleMath::Vector3 forw; // �����ʒu

	void Init(std::string ModelName, std::string TexFolderPath,
		std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader);


	Enemy(std::string ModelName, std::string TexFolderPath, std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader,const Player*Pl);
	~Enemy();

	void DrawInit();
	void Update();
	void MoveUpdate();


	void Draw();


	//���̃Q�b�^�[
	//�����Ă�������̃Q�b�g
	DirectX::SimpleMath::Vector3 Getforward() { return this->forward; };
	//����p�̃Q�b�g
	float GetFov() { return this->viewAngle; };
	//����p�̍ő勗���̃Q�b�g
	float Getlength() { return this->viewDistance; };
	//����p�����̊m�F��bool�^�̃Q�b�g
	bool GetTest() const { return this->test; }
	DirectX::SimpleMath::Vector3 GetSaveForward() { return this->SaveForward; };

	//�ړ����x�̃Z�b�g
	void SetMoveSpeed(float num) { this->MoveSpeed = num; };


	//����͈͂̐F�̃Q�b�g
	DirectX::SimpleMath::Color GetColor() const { return color; }
	//��`�̌��_
	DirectX::SimpleMath::Vector3 GetPoint() { return fanVertices[0].Position; };

	float Getview() { return this->viewX; };

	const Player* getPlayer() const {
		return playerdate;
	};

	EStateType GetState() const { return state; };

	//���̃Z�b�^�[
	//�����Ă�������̃Z�b�g
	void Setforward(DirectX::SimpleMath::Vector3 forwar) { this->forward = forwar; };
	//����p�̃Z�b�g
	void SetFov(float Fov) { this->viewAngle = Fov; };
	//����p�̍ő勗���̃Z�b�g
	void Setlength(float length) { this->viewDistance = length; };
	//����p�����̊m�F��bool�^�̃Z�b�g
	void SetTest(bool value) { this->test = value; }
	//����͈͂̐F�̃Z�b�g
	void SetColor(const DirectX::SimpleMath::Color& col) { color = col; };

	void SetPoint(DirectX::SimpleMath::Vector3 Point) { fanVertices[0].Position = Point; };
	//�����Ă���͈͂̋������w��
	void Setview(float viewX) { this->viewX = viewX; };

	void SetState(EStateType newState) { state = newState; };

	void SetStartPositon(DirectX::SimpleMath::Vector3 Spos) { this->StartPosition = Spos; };
	DirectX::SimpleMath::Vector3 GetStartPositon() { return this->StartPosition; };

	DirectX::SimpleMath::Vector3 PositionForward();

	void viewDraw();

	//����p�̌v�Z
	bool IsInView(DirectX::SimpleMath::Vector3 eyepos, DirectX::SimpleMath::Vector3 lookat, float fov, DirectX::SimpleMath::Vector3 checkpoint, float length);
	//�L�����N�^�[�̕`��
	void EnemyDraw() { Character::Draw(); };
	//�G�̌������v�Z����
	void UpdateRotation();
	//Patrolling�̎��̓���
	void PatrollingMove();
	//Alerted�̎��̓���
	void lookaround();
	//Investigating�̎��̓���
	void InvestigatingMove();

	//�o�H�̃p�X���Z�b�g
	void SetPath(const std::vector<DirectX::SimpleMath::Vector3>& newPath);

	//�p�j���[�g�̃p�X���Z�b�g
	void SetwanderingPath(const std::vector<DirectX::SimpleMath::Vector3>& wanderingPath);

	//�p�j���[�g�̃|�C���g���Q�b�g
	std::vector<DirectX::SimpleMath::Vector3> GetwanderingPath() { return this->wandering_path; };
	

	//�p�j����֐�
	void Wanderaround();

	// �o�H�ɉ����Ĉړ����郁�\�b�h
	void FollowPath();
	//�A�j���[�V�����̃A�b�v�f�[�g
	void AnimUpdate() { Character::Update(); };

	
	//�����蔻��̈ʒu���X�V
	void squareUpdate() {	
		this->m_AnimationObject.m_Position.x = this->square.centerX;
		this->m_AnimationObject.m_Position.y = this->square.centerY;
		this->m_AnimationObject.m_Position.z = this->square.centerZ;
	}
	//hearSound�̃Z�b�^�[
	void SethearSound(bool flg) { this->hearSound = flg; };
	//hearSound�̃Q�b�^�[
	bool GethearSound() { return this->hearSound; };
	//�T���ɍs�����߂�bool�^�̃Z�b�^�[�ƃQ�b�^�[
	void SetSearch(bool flg) { this->Search = flg; };
	bool GetSearch() { return this->Search; };
	//�T�����[�g�ɖ߂�bool�^�̃Z�b�^�[�ƃQ�b�^�[
	void Setback(bool flg) { this->back = flg; };
	bool Getback() { return this->back; };
	//�v���C���[��߂܂������̃Z�b�^�[�ƃQ�b�^�[
	void Setgetcaught(bool flg) { this->getcaught = flg; };
	bool Getgetcaught() { return this->getcaught; };
	//�{������������bool�^�̃Q�b�^�[�ƃZ�b�^�[
	bool GetRookBook() { return this->RookBook; };
	void SetRookBook(bool flg) { this->RookBook = flg; };
	//�{��ǂ�ł���Ƃ���bool�^
	bool GetbookRead() { return this->bookRead; };
	void SetbookRead(bool flg) { this->bookRead = flg; };
	//���[�_�[�̒��ɂ��邩�ǂ�����bool�^�̃Q�b�^�[�ƃZ�b�^�[
	bool GetRaderIn() { return this->RaderIn; };
	void SetRaderIn(bool flg) { this->RaderIn = flg; };
	//���[�_�[��̃|�X
	DirectX::SimpleMath::Vector2 GetRaderPos() { return this->RaderPos; };
	void SetRaderPos(DirectX::SimpleMath::Vector2 pos) { this->RaderPos = pos; }

	//���C���΂�����
	bool RayLookHit();
	bool RayLookBook(DirectX::SimpleMath::Vector3 pos,SQUARE3D square);

	Timer* GetTimer() { return this->time; };

	float GetTime() { return this->Time; };
	float GetTime1() { return this->Time1; };

	void SetTime(float delta) { this->Time = delta; }
	void SetTime1(float delta) { this->Time1 = delta; };

	void Setdeltatime(float delta) { this->deltaTime = delta; };
	float Getdeltatime() { return this->deltaTime; };

	void Getsecurityfov(const std::vector<DirectX::SimpleMath::Vector3>& wanderingPath);
	void securityMove();

	int GetbookCount() { return this->bookCount; };
	void SetbookCount(int num) { this->bookCount = num; };



};


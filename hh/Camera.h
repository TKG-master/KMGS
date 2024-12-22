#pragma once

#include <d3d11.h>  // DirectX11���g�����߂̃w�b�_�[�t�@�C��
#include <DirectXMath.h> // DirextX�̐��w�֘A�̃w�b�_�[�t�@�C��
#include <SimpleMath.h>
#include <DirectXCollision.h>
#include <vector>

class Camera
{
private:

	//S R T�̐錾
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f,0.0f,0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	DirectX::SimpleMath::Vector3 m_Target{};

	DirectX::SimpleMath::Matrix m_ViewMatrix{};

	DirectX::SimpleMath::Matrix projectionMatrix{};

	//�J�����̈ʒu
	float PosX = 0.0f, PosY = 500.0f, PosZ = -350.0f;

	float speed = 0.3f;

	float T = 0.1f;

	float totalTime = 0.0f;

	bool CameraRunning = true;

	//���̓����蔻��̐錾�Ə�����
	DirectX::BoundingSphere boundingSphere = { { 0, 0, 0 }, 1.0f };

	//�l�p�`�̓����蔻��̐錾�Ə�����
	DirectX::BoundingBox boundingBox = { { -1, -1, -1 }, { 1, 1, 1 } };
	


public:
	template<typename T>
	void TSetFocus(const T& focusPosition);

	Camera(DirectX::SimpleMath::Vector3 Pos);
	~Camera();

	//����������
	void Init();
	//�I������
	void Dispose();
	//�A�b�v�f�[�g�̊֐�
	void Update();
	//�`�揈��
	void Draw();

	void II(DirectX::SimpleMath::Vector3 G);

	//�J�����̒ǔ�����
	void LateUpdate(DirectX::SimpleMath::Vector3 playerPos,float deltaTime,float Ypos,bool flog , DirectX::SimpleMath::Vector3 Direction);

	void FocusCamera(DirectX::SimpleMath::Vector3 playerPos, float deltaTime, float Ypos);


	//�J����������ʒu�̍��W��ݒ肷��֐�
	void SetPosition(DirectX::SimpleMath::Vector3 eyePosition);
	//�J�����̌��������ݒ肷��֐�
	void SetFoucus(DirectX::SimpleMath::Vector3 focusPosition);
	//�J�����̈ʒu������Ă���
	DirectX::SimpleMath::Vector3 GetCamPosition();
	//�J�����̌��Ă���ꏊ������Ă���
	DirectX::SimpleMath::Vector3 GetCamforcas();
	//�J�����̈ʒu�̃Z�b�^�[
	void SetCameraPosition();
	//�J�����̌��Ă���ʒu�̃Z�b�^�[
	void GetCameraForcas();
	//�J�����̒ǔ��X�s�[�h�̃Q�b�^�[
	float GetSpeed();
	//�J�����̒ǔ��X�s�[�h�̃Z�b�^�[
	void SetSpeed(float speed);
	//
	void SetFoucusFloat(float& CenterX, float& CenterZ);

	//
	void Setpos(float& CenterX, float& CenterZ);

	void SetT(float a);

	float GetT();

	bool GetCranning() { return this->CameraRunning; };

	void SetCranning(bool run) { this->CameraRunning = run; };

	DirectX::SimpleMath::Matrix GetprojectionMatrix() { return this->projectionMatrix; };
	DirectX::SimpleMath::Matrix GetViewMatrix() { return this->m_ViewMatrix; };


};


// �e���v���[�g���\�b�h�̓��ꉻ�錾
template<>
void Camera::TSetFocus(const DirectX::SimpleMath::Vector3& focusPosition);

template<>
void Camera::TSetFocus(const float& focusPosition);


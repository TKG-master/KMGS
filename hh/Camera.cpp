#include "Camera.h"
#include "renderer.h"
#include "Application.h"
#include "Input.h"
#include <algorithm>
#include "math.h"
#include "easings.h"

using namespace DirectX::SimpleMath;

using namespace DirectX;



Camera::Camera(DirectX::SimpleMath::Vector3 Pos)
{
	this->m_Position = Pos;
	this->m_Target = Vector3(Pos.x, Pos.y = 0.0f, Pos.z += 600.0f);
}

Camera::~Camera()
{
}

void Camera::Init()
{
	////�J�����̍ŏ��̈ʒu�ƌ��Ă���n�_�̏�����
	/*SetPosition(Vector3(PosX, PosY, PosZ));
	SetFoucus(Vector3(0.0f, 0.0f, 0.0f));*/

	//�A�j���[�V�����e�X�g���E�E�E
	m_Position = Vector3(0.0f, 200.0f, -50.0f);
	m_Target = Vector3(0.0f, 0.0f, 0.0f);

}

void Camera::Dispose()
{

}

void Camera::Update()
{

}

void Camera::Draw()
{

	//�J�����s��̍X�V
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	m_ViewMatrix =
		DirectX::XMMatrixLookAtLH(
			m_Position,
			m_Target,
			up
		);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	constexpr float fieldOfView = DirectX::XMConvertToRadians(50.0f);	

	float aspectRatio = static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());
	float nearPlane = 1.0f;
	float farPlane = 3500.0f;

	projectionMatrix =
		DirectX::XMMatrixPerspectiveFovLH(
			fieldOfView,
			aspectRatio,
			nearPlane,
			farPlane
		);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}
//�J�����̒ǔ�
void Camera::LateUpdate(DirectX::SimpleMath::Vector3 TargetPos, float deltaTime,float Ypos,bool flg, DirectX::SimpleMath::Vector3 Direction)
{
	if (flg)
	{
		//�ڕW�̈ʒu�܂ł��v�Z
		Vector3 TargetPosition = TargetPos + Vector3(0.0f, 80.0f, 0.0f);

		//���`�⊮
		float lerpFactor = 0.9f;


		//�x��ăJ�����̈ʒu���v���C���[�ɒǔ������鏈��
		this->m_Position = Vector3::Lerp(this->m_Position, TargetPosition, deltaTime * lerpFactor);	//�����@�P�J�n�n�_�E�Q�I���n�_�E�R�⊮�W���̏���


		//�v���C���[�̈ʒu�ɐݒ�
		this->m_Target = Vector3(Direction.x * 5000.0f,50.0f, Direction.z * 5000.0f);
	}
	else
	{
		//�ڕW�̈ʒu�܂ł��v�Z
		Vector3 TargetPosition = TargetPos + Vector3(PosX, Ypos, PosZ);

		//���`�⊮
		float lerpFactor = 0.9f;


		//�x��ăJ�����̈ʒu���v���C���[�ɒǔ������鏈��
		this->m_Position = Vector3::Lerp(this->m_Position, TargetPosition, deltaTime * lerpFactor);	//�����@�P�J�n�n�_�E�Q�I���n�_�E�R�⊮�W���̏���

		//this->m_Target = TargetPos + Vector3(PosX, PosY, PosZ);

		//�v���C���[�̈ʒu�ɐݒ�
		this->m_Target = TargetPos;
	}
}

void Camera::FocusCamera(DirectX::SimpleMath::Vector3 TargetPos, float deltaTime, float Ypos)
{
	//�ڕW�̈ʒu�܂ł��v�Z
	Vector3 TargetPosition = TargetPos + Vector3(PosX, Ypos, PosZ);

	//���`�⊮
	float lerpFactor = 0.9f;


	//�x��ăJ�����̈ʒu���v���C���[�ɒǔ������鏈��
	this->m_Position = Vector3::Lerp(this->m_Position, TargetPosition, deltaTime * lerpFactor);	//�����@�P�J�n�n�_�E�Q�I���n�_�E�R�⊮�W���̏���

	this->m_Target = TargetPos + Vector3(PosX, PosY, PosZ);

	//�v���C���[�̈ʒu�ɐݒ�
	this->m_Target = TargetPos;
}

//�ʒu�̃Z�b�g
void Camera::SetPosition(DirectX::SimpleMath::Vector3 eyePosition)
{
	m_Position = eyePosition;
}
//���_�̃Z�b�g
void Camera::SetFoucus(DirectX::SimpleMath::Vector3 focusPosition)
{
	m_Target = focusPosition;
}

//�J�����̈ʒu���Q�b�g
DirectX::SimpleMath::Vector3 Camera::GetCamPosition() const
{
	return this->m_Position;
}

DirectX::SimpleMath::Vector3 Camera::GetCamforcas()
{
	return this->m_Target;
}

void Camera::SetCameraPosition()
{
	this->m_Position;
}

void Camera::GetCameraForcas()
{
	this->m_Target;
}
float Camera::GetSpeed()
{
	return this->speed;
}

void Camera::SetSpeed(float speed)
{
	this->speed = speed;
}

void Camera::SetFoucusFloat(float& CenterX, float& CenterZ)
{
	m_Target.x = CenterX;
	m_Target.z = CenterZ;

}

void Camera::LightDraw()
{
	//�J�����s��̍X�V
	Vector3 up = Vector3(0.0f, 0.0f, -1.0f);
	m_ViewMatrix =
		DirectX::XMMatrixLookAtLH(
			m_Position,
			m_Target,
			up
		);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	constexpr float fieldOfView = DirectX::XMConvertToRadians(50.0f);

	float aspectRatio = static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());
	float nearPlane = 1.0f;
	float farPlane = 3500.0f;

	projectionMatrix =
		DirectX::XMMatrixOrthographicLH(
			500.0f,
			500.0f,
			0.0f,
			2000.0f
		);

	Renderer::SetLightProjectionMatrix(&projectionMatrix);
	Renderer::SetProjectionMatrix(&projectionMatrix);
	Renderer::SetLightViewMatrix(&m_ViewMatrix);

}

void Camera::Setpos(float& CenterX, float& CenterZ)
{
	m_Position.x = CenterX;
	m_Position.z = CenterZ;
}

void Camera::SetT(float a)
{
	T = a;
}

float Camera::GetT()
{
	return T;
}


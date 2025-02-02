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
	////カメラの最初の位置と見ている地点の初期化
	/*SetPosition(Vector3(PosX, PosY, PosZ));
	SetFoucus(Vector3(0.0f, 0.0f, 0.0f));*/

	//アニメーションテスト中・・・
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

	//カメラ行列の更新
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
//カメラの追尾
void Camera::LateUpdate(DirectX::SimpleMath::Vector3 TargetPos, float deltaTime,float Ypos,bool flg, DirectX::SimpleMath::Vector3 Direction)
{
	if (flg)
	{
		//目標の位置までを計算
		Vector3 TargetPosition = TargetPos + Vector3(0.0f, 80.0f, 0.0f);

		//線形補完
		float lerpFactor = 0.9f;


		//遅れてカメラの位置をプレイヤーに追尾させる処理
		this->m_Position = Vector3::Lerp(this->m_Position, TargetPosition, deltaTime * lerpFactor);	//引数　１開始地点・２終了地点・３補完係数の順番


		//プレイヤーの位置に設定
		this->m_Target = Vector3(Direction.x * 5000.0f,50.0f, Direction.z * 5000.0f);
	}
	else
	{
		//目標の位置までを計算
		Vector3 TargetPosition = TargetPos + Vector3(PosX, Ypos, PosZ);

		//線形補完
		float lerpFactor = 0.9f;


		//遅れてカメラの位置をプレイヤーに追尾させる処理
		this->m_Position = Vector3::Lerp(this->m_Position, TargetPosition, deltaTime * lerpFactor);	//引数　１開始地点・２終了地点・３補完係数の順番

		//this->m_Target = TargetPos + Vector3(PosX, PosY, PosZ);

		//プレイヤーの位置に設定
		this->m_Target = TargetPos;
	}
}

void Camera::FocusCamera(DirectX::SimpleMath::Vector3 TargetPos, float deltaTime, float Ypos)
{
	//目標の位置までを計算
	Vector3 TargetPosition = TargetPos + Vector3(PosX, Ypos, PosZ);

	//線形補完
	float lerpFactor = 0.9f;


	//遅れてカメラの位置をプレイヤーに追尾させる処理
	this->m_Position = Vector3::Lerp(this->m_Position, TargetPosition, deltaTime * lerpFactor);	//引数　１開始地点・２終了地点・３補完係数の順番

	this->m_Target = TargetPos + Vector3(PosX, PosY, PosZ);

	//プレイヤーの位置に設定
	this->m_Target = TargetPos;
}

//位置のセット
void Camera::SetPosition(DirectX::SimpleMath::Vector3 eyePosition)
{
	m_Position = eyePosition;
}
//視点のセット
void Camera::SetFoucus(DirectX::SimpleMath::Vector3 focusPosition)
{
	m_Target = focusPosition;
}

//カメラの位置をゲット
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
	//カメラ行列の更新
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


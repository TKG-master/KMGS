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

void Camera::Update(DirectX::SimpleMath::Vector3 TargetPos)
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

	Matrix projectionMatrix;
	projectionMatrix =
		DirectX::XMMatrixPerspectiveFovLH(
			fieldOfView,
			aspectRatio,
			nearPlane,
			farPlane
		);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}

void Camera::II(DirectX::SimpleMath::Vector3 G)
{
	this->m_Position.x = (pow(1 - T, 2) * 0.0f)
		+ (2 * T) * (1 - T) * ((0.0f + G.x) / 2)
		+ (pow(T, 2) * G.x);

	this->m_Position.y = (pow(1 - T, 2) * 250.0f)
		+ (2 * T) * (1 - T) * ((250.0f + G.y) / 2)
		+ (pow(T, 2) * G.y);

	this->m_Position.z = (pow(1 - T, 2) * -150.0f)
		+ (2 * T) * (1 - T) * ((-150.0f + G.z) / 2)
		+ (pow(T, 2) * G.z);
}

//カメラの追尾
void Camera::LateUpdate(DirectX::SimpleMath::Vector3 TargetPos, float deltaTime)
{
	//目標の位置までを計算
	Vector3 TargetPosition = TargetPos + Vector3(PosX, PosY, PosZ);

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
DirectX::SimpleMath::Vector3 Camera::GetCamPosition()
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

// テンプレートメソッドの特殊化実装
template<>
void Camera::TSetFocus(const DirectX::SimpleMath::Vector3& focusPosition)
{
	m_Target = focusPosition;
}

template<>
void Camera::TSetFocus(const float& focusPosition)
{
	m_Target = DirectX::SimpleMath::Vector3(focusPosition); // 任意の軸にフォーカスを設定
}


#pragma once

#include <d3d11.h>  // DirectX11を使うためのヘッダーファイル
#include <DirectXMath.h> // DirextXの数学関連のヘッダーファイル
#include <SimpleMath.h>
#include <DirectXCollision.h>
#include <vector>

class Camera
{
private:

	//S R Tの宣言
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f,0.0f,0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	DirectX::SimpleMath::Vector3 m_Target{};

	DirectX::SimpleMath::Matrix m_ViewMatrix{};

	DirectX::SimpleMath::Matrix projectionMatrix{};

	//カメラの位置
	float PosX = 0.0f, PosY = 500.0f, PosZ = -350.0f;

	float speed = 0.3f;

	float T = 0.1f;

	float totalTime = 0.0f;

	bool CameraRunning = true;

	//球の当たり判定の宣言と初期化
	DirectX::BoundingSphere boundingSphere = { { 0, 0, 0 }, 1.0f };

	//四角形の当たり判定の宣言と初期化
	DirectX::BoundingBox boundingBox = { { -1, -1, -1 }, { 1, 1, 1 } };
	


public:
	template<typename T>
	void TSetFocus(const T& focusPosition);

	Camera(DirectX::SimpleMath::Vector3 Pos);
	~Camera();

	//初期化処理
	void Init();
	//終了処理
	void Dispose();
	//アップデートの関数
	void Update();
	//描画処理
	void Draw();

	void II(DirectX::SimpleMath::Vector3 G);

	//カメラの追尾処理
	void LateUpdate(DirectX::SimpleMath::Vector3 playerPos,float deltaTime,float Ypos,bool flog , DirectX::SimpleMath::Vector3 Direction);

	void FocusCamera(DirectX::SimpleMath::Vector3 playerPos, float deltaTime, float Ypos);


	//カメラがいる位置の座標を設定する関数
	void SetPosition(DirectX::SimpleMath::Vector3 eyePosition);
	//カメラの見る方向を設定する関数
	void SetFoucus(DirectX::SimpleMath::Vector3 focusPosition);
	//カメラの位置を取ってくる
	DirectX::SimpleMath::Vector3 GetCamPosition();
	//カメラの見ている場所を取ってくる
	DirectX::SimpleMath::Vector3 GetCamforcas();
	//カメラの位置のセッター
	void SetCameraPosition();
	//カメラの見ている位置のセッター
	void GetCameraForcas();
	//カメラの追尾スピードのゲッター
	float GetSpeed();
	//カメラの追尾スピードのセッター
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


// テンプレートメソッドの特殊化宣言
template<>
void Camera::TSetFocus(const DirectX::SimpleMath::Vector3& focusPosition);

template<>
void Camera::TSetFocus(const float& focusPosition);


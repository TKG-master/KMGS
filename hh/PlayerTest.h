#pragma once
#include "CBoxMesh.h"
#include "Camera.h"
#include "Input.h"


//開発のための試作を試すクラス
class PlayerTest
{
private:
	//SRT情報（姿勢情報）
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);



	//描画のための情報（メッシュにかかわる情報）
	CIndexBuffer				m_IndexBuffer;
	CVertexBuffer<VERTEX_3D>	m_VertexBuffer;

	//描画の為の情報（見た目にかかわる部分）
	CShader		m_Shader;
	CMaterial	m_Material;
	CTexture	m_Texture;

	//向いている方向
	DirectX::XMFLOAT3 forward = { 0,0,1 };
	//移動スピードを持つ変数
	float movespeed = 1.0f;



public:
	//コンストラクタ
	PlayerTest();
	//デスストラクタ
	~PlayerTest();

	//プレイヤーの更新
	void Update();
	//初期化
	void Init();
	//描画
	void Draw();
	//プレイヤーの移動速度をセット
	void SetSpeed(float ac) { movespeed = ac; };
	//プレイヤーの速度をゲット
	float GetSpeed();
	float Move(float a);
	//向いている情報をゲット
	DirectX::XMFLOAT3 GetForward();
	//プレイヤーのS・R・Tをゲットできる関数
	DirectX::SimpleMath::Vector3 GetPosition();
	DirectX::SimpleMath::Vector3 GetRoatation();
	DirectX::SimpleMath::Vector3 GetScale();

	//プレイヤーのS R Tをセットする関数
	void SetPosition(DirectX::SimpleMath::Vector3 pos);
	void SetRoatation(DirectX::SimpleMath::Vector3 roa);
	void SetScale(DirectX::SimpleMath::Vector3 sca);

	

};





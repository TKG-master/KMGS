#pragma once
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CMaterial.h"
#include "CTexture.h"


class Enemy;

class Radar
{
private:
	DirectX::SimpleMath::Vector2 m_RadarCenter; // レーダーの中心位置
	std::vector<DirectX::SimpleMath::Vector2> m_EnemyPositions; // 複数の敵の位置
	DirectX::SimpleMath::Vector2 relativePos;
	DirectX::SimpleMath::Vector3 playerpos;
	std::vector<int> m_EnemyIndices;

	//レーダー上の座標への変換した値を保持する
	float differenceX = 0.0f;
	float differenceY = 0.0f;

	//レーダー上の敵の位置のXとY
	float SaveANSX = 0.0f;
	float SaveANSY = 0.0f;

	// 長方形のレーダー範囲内に敵がいるかをチェック
	float halfWidth = 100.0f; // レーダーの半幅
	float halfHeight = 100.0f; // レーダーの半高

	//レーダーの原点から敵の位置の点の差分
	float Savedistance = 0.0f;

	// 追加: スキャンラインの角度を保持するメンバ変数
	float m_ScanLineAngle = 0.0f;

	// 1フレームごとに回転する角度（度単位）
	float m_ScanLineSpeed = 0.0001f; 

	CIndexBuffer				m_IndexBuffer;
	CVertexBuffer<VERTEX_3D>	m_VertexBuffer;
	CShader						m_Shader;
	CMaterial					m_Material;
	CTexture					m_Texture;

public:
	//初期化
	void Init();
	//敵の位置と自分の位置の差分を2Dの位置に変換
	void Update(DirectX::SimpleMath::Vector3 playerPosition, std::vector<Enemy*> enemies);
	//描画
	void Draw(const std::vector<Enemy*>& enemies);

	void Dispose();


	DirectX::SimpleMath::Vector2 GetRadarCenter() { return m_RadarCenter; };
	DirectX::SimpleMath::Vector2 GetrelativePos() { return relativePos; };

	float SaveANSx() { return SaveANSX; };
	float SaveANSy() { return SaveANSY; };

};


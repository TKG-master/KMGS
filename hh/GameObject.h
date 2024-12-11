#pragma once
#include <DirectXMath.h> // DirextXの数学関連のヘッダーファイル
#include <SimpleMath.h>
#include "AnimObj.h"
#include "CCollision.h"

class GameObject
{

protected:

	//SRT情報（姿勢情報）
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(0.1f, 0.1f, 0.1f);

	// ブレンドレート
	float BlendRate = 0.0f;

	// アニメーションインデックス
	int idx = 0;

	// 重力
	float gravity = 9.81f;

public:

	GameObject();
	~GameObject();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Uninit();

	void AnimInit();
	void AnimUpdate();
	void AnimDraw();

};


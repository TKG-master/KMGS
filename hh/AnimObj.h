#pragma once
#include	<simplemath.h>
#include	"BoneCombMatrix.h"
#include	"CAnimationMesh.h"

class AnimObj
{
	// SRT情報
	DirectX::SimpleMath::Vector3 m_Position = { 0,0,0 };
	DirectX::SimpleMath::Vector3 m_Rotation = { 0,0,0 };
	DirectX::SimpleMath::Vector3 m_Scale = { 0.1f,0.1f,0.1f };

	// ボーンコンビネーション行列用定数バッファ内容
	BoneCombMatrix m_BoneCombMatrix{};							// 20240723

	// アニメーションメッシュ
	CAnimationMesh* m_AnimMesh = nullptr;

	// 現在のアニメーション
	aiAnimation* m_CurrentAnimation = nullptr;
	aiAnimation* m_FromAnimation = nullptr;
	aiAnimation* m_ToAnimation = nullptr;

	// 現在フレーム
	float m_CurrentFrame = 0;
	// ブレンドレイト
	float m_BlendRate = 0.0f;									// モーションのブレンド率

public:
	void Init();
	void Update(float dt);

	void BlendUpdate(float dt);

	void Draw(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 Scal , DirectX::SimpleMath::Vector3 Roatat);
	void SetAnimationMesh(CAnimationMesh* animmesh) { m_AnimMesh = animmesh; }
	void SetPosition(DirectX::SimpleMath::Vector3 pos) { m_Position = pos; }
	void SetScale(DirectX::SimpleMath::Vector3 scale) { m_Scale = scale; }
	void SetRotation(DirectX::SimpleMath::Vector3 rotation) { m_Rotation = rotation; }

	void SetCurrentAnimation(aiAnimation* anim) { m_CurrentAnimation = anim; }

	void SetFromAnimation(aiAnimation* anim) { m_FromAnimation = anim; }

	void SetToAnimation(aiAnimation* anim) { m_ToAnimation = anim; }

	void SetBlendRate(float rate) { m_BlendRate = rate; }


};


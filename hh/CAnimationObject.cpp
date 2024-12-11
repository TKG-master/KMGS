#include "CAnimationObject.h"

using namespace DirectX::SimpleMath;

void CAnimationObject::Init()
{
	// ボーンコンビネーション行列初期化
	m_BoneCombMatrix.Create();							// 20240723 
}

void CAnimationObject::Update(float dt)
{
	int frame = static_cast<int>(m_CurrentFrame);

	// アニメーションメッシュのカレントアニメーションをセット
	m_AnimMesh->SetCurentAnimation(m_CurrentAnimation);

	// アニメーションメッシュ更新
	m_AnimMesh->Update(m_BoneCombMatrix, frame);

	// フレーム更新	
	m_CurrentFrame += dt;
}

void CAnimationObject::BlendUpdate(float dt)
{
	int frame = static_cast<int>(m_CurrentFrame);

	// アニメーションメッシュのブレンドアニメーションをセット
	m_AnimMesh->SetFromAnimation(m_FromAnimation);
	m_AnimMesh->SetToAnimation(m_ToAnimation);

	m_AnimMesh->BlendUpdate(m_BoneCombMatrix, frame, frame, m_BlendRate);

	// フレーム更新	
	m_CurrentFrame += dt;
}

void CAnimationObject::Draw()
{
	Matrix rmtx = Matrix::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(m_Rotation.y), // Yaw (度数 → ラジアン)
		DirectX::XMConvertToRadians(m_Rotation.x), // Pitch (度数 → ラジアン)
		DirectX::XMConvertToRadians(m_Rotation.z)  // Roll (度数 → ラジアン)
	);
	Matrix smtx = Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);
	Matrix tmtx = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);

	Matrix wmtx = smtx * rmtx * tmtx;

	Renderer::SetWorldMatrix(&wmtx);

	// ボーンコンビネーション行列用定数バッファ更新
	m_BoneCombMatrix.Update();

	// 定数バッファGPUへセット
	m_BoneCombMatrix.SetGPU();

	// メッシュ描画
	m_AnimMesh->Draw();
}

void CAnimationObject::ModifyRotation()
{
	if (m_Rotation.x < 0)
	{
		m_Rotation.x = 359;
	}
	if (m_Rotation.y < 0)
	{
		m_Rotation.y = 359;
	}
	if (m_Rotation.z < 0)
	{
		m_Rotation.z = 359;
	}

	if (m_Rotation.x >= 360)
	{
		m_Rotation.x = 0;
	}
	if (m_Rotation.y >= 360)
	{
		m_Rotation.y = 0;
	}
	if (m_Rotation.z >= 360)
	{
		m_Rotation.z = 0;
	}
}
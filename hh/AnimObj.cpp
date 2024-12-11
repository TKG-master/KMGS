#include "AnimObj.h"

using namespace DirectX::SimpleMath;

void AnimObj::Init()
{
	// ボーンコンビネーション行列初期化
	m_BoneCombMatrix.Create();							// 20240723 

}

void AnimObj::Update(float dt)
{
	int frame = static_cast<int>(m_CurrentFrame);

	// アニメーションメッシュのカレントアニメーションをセット
	m_AnimMesh->SetCurentAnimation(m_CurrentAnimation);

	// アニメーションメッシュ更新
	m_AnimMesh->Update(m_BoneCombMatrix, frame);

	// フレーム更新	
	m_CurrentFrame += dt;

}

void AnimObj::BlendUpdate(float dt)
{
	int frame = static_cast<int>(m_CurrentFrame);

	// アニメーションメッシュのブレンドアニメーションをセット
	m_AnimMesh->SetFromAnimation(m_FromAnimation);
	m_AnimMesh->SetToAnimation(m_ToAnimation);

	m_AnimMesh->BlendUpdate(m_BoneCombMatrix, frame, frame, m_BlendRate);

	// フレーム更新	
	m_CurrentFrame += dt;
}

void AnimObj::Draw(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 Scal , DirectX::SimpleMath::Vector3 Roatat)
{
	Matrix rmtx = Matrix::CreateFromYawPitchRoll(Roatat.y, Roatat.x, Roatat.z);
	Matrix smtx = Matrix::CreateScale(Scal.x, Scal.y, Scal.z);
	Matrix tmtx = Matrix::CreateTranslation(pos.x, pos.y, pos.z);

	Matrix wmtx = smtx * rmtx * tmtx;

	Renderer::SetWorldMatrix(&wmtx);

	// ボーンコンビネーション行列用定数バッファ更新
	m_BoneCombMatrix.Update();

	// 定数バッファGPUへセット
	m_BoneCombMatrix.SetGPU();

	// メッシュ描画
	m_AnimMesh->Draw();
}

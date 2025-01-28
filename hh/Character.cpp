#include "Character.h"

bool Character::AnimationBrend()
{
	//From取得
	aiAnimation* fromanimation = m_AnimationData[m_FromAnimationName].GetAnimation(m_FromAnimationName);
	m_AnimationObject.SetFromAnimation(fromanimation);

	//To取得
	aiAnimation* toanimation = m_AnimationData[m_ToAnimationName].GetAnimation(m_ToAnimationName);
	m_AnimationObject.SetToAnimation(toanimation);

	//fromとtoが一致、ブレンドさせない場合ここで終了させる
	if (fromanimation == toanimation) { return false; }

	// ブレンドレート設定
	m_BlendRate += m_AnimationBrendSpeed;
	if (m_BlendRate >= 1.0f)
	{
		//ブレンド完全に終了後
		m_BlendRate = 1.0f;
		m_AnimationObject.SetBlendRate(m_BlendRate);
		//変え切ったのでFromにToをいれる
		m_FromAnimationName = m_ToAnimationName;
		m_BlendRate = 0.0f;
		this->AnimEndState = true;
		return true;
	}
	m_AnimationObject.SetBlendRate(m_BlendRate);
	this->AnimEndState = false;
	return false;
}

void Character::Init(
	std::string ModelName, std::string TexFolderPath,
	std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader)
{
	DepthS.Create("shader/vertexLightingOneSkinVS.hlsl","shader/PS_DepthWrite.hlsl");


	STATUS = IDLE;

	// アニメーションメッシュ読み込み
	m_AnimationMesh.Load(ModelName, TexFolderPath);

	// オブジェクトにメッシュをセット
	m_AnimationObject.SetAnimationMesh(&m_AnimationMesh);

	// シェーダオブジェクト生成
	m_Shader.Create(vShader, pShader);

	// アニメーションデータ読み込み
	for (int i = 0; i < MotionName.size(); i++)
	{
		m_AnimationData[MotionName[i].MotionKey].LoadAnimation
		(MotionName[i].MotionFile, MotionName[i].MotionKey);
	}

	// アニメーションデータ取得
	const std::string s = MotionName[0].MotionKey;
	aiAnimation* animation = m_AnimationData[s].GetAnimation(s);
	// 現在のアニメーションをセット
	m_AnimationObject.SetCurrentAnimation(animation);

	// 初期化
	m_AnimationObject.Init();

	// 位置設定
	m_AnimationObject.SetPosition(DirectX::SimpleMath::Vector3(0, 0, 0));

	// スケール設定
	m_AnimationObject.SetScale(DirectX::SimpleMath::Vector3(0.08f, 0.08f, 0.08f));

	// 最初のモーションキー保存
	m_FromAnimationName = MotionName[0].MotionKey;
	m_ToAnimationName = MotionName[0].MotionKey;


}

void Character::EnemyInit(CAnimationMesh m_AnimationMesh, std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader)
{
	STATUS = IDLE;

	// オブジェクトにメッシュをセット
	m_AnimationObject.SetAnimationMesh(&m_AnimationMesh);

	// シェーダオブジェクト生成
	m_Shader.Create(vShader, pShader);

	// アニメーションデータ読み込み
	for (int i = 0; i < MotionName.size(); i++)
	{
		m_AnimationData[MotionName[i].MotionKey].LoadAnimation
		(MotionName[i].MotionFile, MotionName[i].MotionKey);
	}

	// アニメーションデータ取得
	const std::string s = MotionName[0].MotionKey;
	aiAnimation* animation = m_AnimationData[s].GetAnimation(s);
	// 現在のアニメーションをセット
	m_AnimationObject.SetCurrentAnimation(animation);

	// 初期化
	m_AnimationObject.Init();

	// 位置設定
	m_AnimationObject.SetPosition(DirectX::SimpleMath::Vector3(0, 0, 0));

	// スケール設定
	m_AnimationObject.SetScale(DirectX::SimpleMath::Vector3(0.08f, 0.08f, 0.08f));

	// 最初のモーションキー保存
	m_FromAnimationName = MotionName[0].MotionKey;
	m_ToAnimationName = MotionName[0].MotionKey;
}

void Character::UnInit()
{

}

void Character::Update()
{
	// アニメーションブレンド更新
	AnimationBrend();
	// アニメーションオブジェクト更新
	m_AnimationObject.BlendUpdate(m_AnimationSpeed);

	this->square.centerX = this->m_AnimationObject.m_Position.x;
	this->square.centerY = this->m_AnimationObject.m_Position.y;
	this->square.centerZ = this->m_AnimationObject.m_Position.z;

}

void Character::Draw()
{
	m_Shader.SetGPU();
	m_AnimationObject.Draw();


}

void Character::ModifyRotation()
{
	if (m_AnimationObject.m_Rotation.x < 0)
	{
		m_AnimationObject.m_Rotation.x = 359;
	}
	if (m_AnimationObject.m_Rotation.y < 0)
	{
		m_AnimationObject.m_Rotation.y = 359;
	}
	if (m_AnimationObject.m_Rotation.z < 0)
	{
		m_AnimationObject.m_Rotation.z = 359;
	}

	if (m_AnimationObject.m_Rotation.x >= 360)
	{
		m_AnimationObject.m_Rotation.x = 0;
	}
	if (m_AnimationObject.m_Rotation.y >= 360)
	{
		m_AnimationObject.m_Rotation.y = 0;
	}
	if (m_AnimationObject.m_Rotation.z >= 360)
	{
		m_AnimationObject.m_Rotation.z = 0;
	}
}

void Character::CollisionInit(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 size)
{
	//立方体の中心点
	this->square.centerX = pos.x;
	this->square.centerY = pos.y;
	this->square.centerZ = pos.z;
	//立方体のサイズ
	this->square.sizeX = size.x;
	this->square.sizeY = size.y;
	this->square.sizeZ = size.z;
}

void Character::ShadowDraw()
{
	DepthS.SetGPU();
	m_AnimationObject.Draw();
}

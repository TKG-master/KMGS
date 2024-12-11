#include	"GameObject.h"
#include	<SimpleMath.h>
#include	<memory>
#include	"CShader.h"
#include	"CAnimationData.h"
#include	"CAnimationMesh.h"

using namespace DirectX::SimpleMath;

// シェーダー
static CShader	g_Shader;

// アニメーションデータ
static CAnimationData g_AnimationData[2];

// アニメーションメッシュ
static CAnimationMesh g_AnimationMesh{};

// アニメーションオブジェクト
AnimObj g_AnimationObject[1];


GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::Init()
{
	//アニメーションの初期化
	this->AnimInit();
}

void GameObject::Update()
{
	//アニメーションのアップデート
	this->AnimUpdate();
}

void GameObject::Draw()
{
	//アニメーションの描画
	this->AnimDraw();
}

void GameObject::Uninit()
{

}

void GameObject::AnimInit()
{
	std::vector<std::string> filename =
	{
		"assets/model/akai.fbx",
	};

	std::string texdirectory =
	{
		"assets/model",				// テクスチャあり（内部）			OK
	};

	std::vector<std::string> motionfile =
	{
		"assets/model/Akai_Idle.fbx",
		"assets/model/Akai_Run.fbx",
	};

	// モデル読み込み
	std::string f = filename[0];

	// アニメーションメッシュ読み込み
	g_AnimationMesh.Load(f, texdirectory);


	// オブジェクトにメッシュをセット
	for (auto& obj : g_AnimationObject)
	{
		obj.SetAnimationMesh(&g_AnimationMesh);
	}

	// シェーダオブジェクト生成
	g_Shader.Create("shader/vertexLightingOneSkinVS.hlsl", "shader/vertexLightingPS.hlsl");

	// アニメーションデータ読み込み

	g_AnimationData[0].LoadAnimation(motionfile[0], "Idle");
	g_AnimationData[1].LoadAnimation(motionfile[1], "Run");

	// アニメーションデータ取得
	aiAnimation* animation1 = g_AnimationData[0].GetAnimation("Idle");
	aiAnimation* animation2 = g_AnimationData[1].GetAnimation("Run");

	// 現在のアニメーションをセット
	g_AnimationObject[0].SetCurrentAnimation(animation1);

	// 初期化
	g_AnimationObject[0].Init();

	// 位置設定
	g_AnimationObject[0].SetPosition(this->m_Position);

	// スケール設定
	g_AnimationObject[0].SetScale(this->m_Scale);
}

void GameObject::AnimUpdate()
{
	aiAnimation* fromanimation = g_AnimationData[0].GetAnimation("Idle");

	g_AnimationObject[0].SetFromAnimation(fromanimation);

	aiAnimation* toanimation = g_AnimationData[1].GetAnimation("Run");

	g_AnimationObject[0].SetToAnimation(toanimation);

	// ブレンドレート設定
	g_AnimationObject[0].SetBlendRate(this->BlendRate);

	// アニメーションオブジェクト更新
	g_AnimationObject[0].BlendUpdate(1.0f);					// ここで渡しているのは更新時間

}

void GameObject::AnimDraw()
{
	g_Shader.SetGPU();

	for (auto& obj : g_AnimationObject) {
		obj.Draw(this->m_Position, this->m_Scale, this->m_Rotation);
	}

}

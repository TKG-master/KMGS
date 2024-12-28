#pragma once
#include <SimpleMath.h>
#include "CShader.h"
#include "Character.h"
#include "Timer.h"
#include "EnemyAI.h"

class EnemyAI;

class GameUI;

class Player;

class Enemy : public Character
{
private:

	EnemyAI* AI;

	Timer* time;

	GameUI* UI;
	GameUI* suspiciousUI;

	//向いている方向
	DirectX::SimpleMath::Vector3 forward = { 0.0f,0.0f,-1.0f };
	//視野範囲の色
	DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(1.0f, 0.0f, 0.0f, 0.8f);
	//扇形の点の場所
	DirectX::SimpleMath::Vector3 point;
	//次の地点
	DirectX::SimpleMath::Vector3 nextPosition;
	//動く速度
	float MoveSpeed = 0.8f;
	//視野範囲を描画するために必要な行列
	DirectX::SimpleMath::Matrix rotation;

	//現在の状態を維持する
	EStateType state = EStateType::Patrolling;

	// 経路情報を保持するメンバ変数
	std::vector<DirectX::SimpleMath::Vector3> path;
	int currentPathIndex = 0;
	//徘徊するルートのポイント格納の配列
	std::vector<DirectX::SimpleMath::Vector3> wandering_path;
	//警戒する場合の向き
	std::vector<DirectX::SimpleMath::Vector3> forward_path;
	int currentwanderingpathIndex = 0;
	//次の徘徊の目的地
	DirectX::SimpleMath::Vector3 targetPos;
	// 現在の位置
	DirectX::SimpleMath::Vector3 currentPosition;

	//例のVector3
	DirectX::SimpleMath::Vector3 rayDirection;
	//45固定
	float rayY = 45.0f;
	//例がどこまで伸ばして当たったか
	float hitDis = 0.0f;

	float distance;


	//音が聞こえたか？
	bool hearSound = false;
	//経路探索中のbool型
	bool Search = false;
	//帰宅中
	bool back = false;
	//捕まった
	bool getcaught = false;
	//見渡しているときのブール型
	bool secrity = false;

	float deltaTime = 0.005f;
	float Time1 = 0.5;
	float Time = 0.0f;

	// 移動量を計算
	DirectX::SimpleMath::Vector3 direction;

	// 視野範囲の最大角度
	float maxLookAngle = 45.0f;  // 最大30度の範囲で左右に回転
	// 右に向かっているかどうか
	bool isLookingRight = false;
	//振り向ている最中か？
	bool turn = false;

	float lookSpeed = 0.01f; // 回転速度
	//プレイヤーのデーター（読み取り用）
	const Player* playerdate;

	//扇形を描画するときのセグメント数
	static constexpr int numSegments = 50;
	std::vector<VERTEX_3D> fanVertices = std::vector<VERTEX_3D>(numSegments + 2);

	std::vector<DirectX::SimpleMath::Vector3> intersectionPoints;

	// 視野角の設定
	float viewAngle = 0.8f; // 視野角
	float viewDistance = 300.0f; // 視野の距離
	bool test = false;
	float viewX = 2.0f;
	float viewZ = 2.8f;
	DirectX::SimpleMath::Vector3 SaveForward;

	CIndexBuffer				e_IndexBuffer;
	CVertexBuffer<VERTEX_3D>	e_VertexBuffer;
	CMaterial					e_Material;
	CTexture					e_Texture;
	CShader						e_Shader;

public:

	DirectX::SimpleMath::Vector3 forw; // 初期位置

	void Init(std::string ModelName, std::string TexFolderPath,
		std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader);

	void UIInit(int nam);

	Enemy(std::string ModelName, std::string TexFolderPath, std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader,const Player*Pl);
	~Enemy();

	void DrawInit();
	void Update();
	void MoveUpdate();


	void Draw();


	//情報のゲッター
	//向いている方向のゲット
	DirectX::SimpleMath::Vector3 Getforward() { return this->forward; };
	//視野角のゲット
	float GetFov() { return this->viewAngle; };
	//視野角の最大距離のゲット
	float Getlength() { return this->viewDistance; };
	//視野角内かの確認のbool型のゲット
	bool GetTest() const { return this->test; }
	DirectX::SimpleMath::Vector3 GetSaveForward() { return this->SaveForward; };
	//視野範囲の色のゲット
	DirectX::SimpleMath::Color GetColor() const { return color; }
	//扇形の原点
	DirectX::SimpleMath::Vector3 GetPoint() { return fanVertices[0].Position; };

	float Getview() { return this->viewX; };

	const Player* getPlayer() const {
		return playerdate;
	};

	EStateType GetState() const { return state; };

	//情報のセッター
	//向いている方向のセット
	void Setforward(DirectX::SimpleMath::Vector3 forwar) { this->forward = forwar; };
	//視野角のセット
	void SetFov(float Fov) { this->viewAngle = Fov; };
	//視野角の最大距離のセット
	void Setlength(float length) { this->viewDistance = length; };
	//視野角内化の確認のbool型のセット
	void SetTest(bool value) { this->test = value; }
	//視野範囲の色のセット
	void SetColor(const DirectX::SimpleMath::Color& col) { color = col; };

	void SetPoint(DirectX::SimpleMath::Vector3 Point) { fanVertices[0].Position = Point; };
	//見えている範囲の距離を指定
	void Setview(float viewX) { this->viewX = viewX; };

	void SetState(EStateType newState) { state = newState; };

	DirectX::SimpleMath::Vector3 PositionForward();

	void viewDraw();

	void UIDraw();

	//視野角の計算
	bool IsInView(DirectX::SimpleMath::Vector3 eyepos, DirectX::SimpleMath::Vector3 lookat, float fov, DirectX::SimpleMath::Vector3 checkpoint, float length);
	//キャラクターの描画
	void EnemyDraw() { Character::Draw(); };
	//敵の向きを計算する
	void UpdateRotation();
	//Patrollingの時の動作
	void PatrollingMove();
	//Alertedの時の動作
	void lookaround();
	//Investigatingの時の動作
	void InvestigatingMove();

	//経路のパスをセット
	void SetPath(const std::vector<DirectX::SimpleMath::Vector3>& newPath);

	//徘徊ルートのパスをセット
	void SetwanderingPath(const std::vector<DirectX::SimpleMath::Vector3>& wanderingPath);

	void SetSecurity(int num);

	//徘徊ルートのポイントをゲット
	std::vector<DirectX::SimpleMath::Vector3> GetwanderingPath() { return this->wandering_path; };
	

	//徘徊する関数
	void Wanderaround();

	// 経路に沿って移動するメソッド
	void FollowPath();
	//アニメーションのアップデート
	void AnimUpdate() { Character::Update(); };

	
	//当たり判定の位置を更新
	void squareUpdate() {	
		this->m_AnimationObject.m_Position.x = this->square.centerX;
		this->m_AnimationObject.m_Position.y = this->square.centerY;
		this->m_AnimationObject.m_Position.z = this->square.centerZ;
	}
	//hearSoundのセッター
	void SethearSound(bool flg) { this->hearSound = flg; };
	//hearSoundのゲッター
	bool GethearSound() { return this->hearSound; };
	//探しに行くためのbool型のセッターとゲッター
	void SetSearch(bool flg) { this->Search = flg; };
	bool GetSearch() { return this->Search; };
	//探索ルートに戻るbool型のセッターとゲッター
	void Setback(bool flg) { this->back = flg; };
	bool Getback() { return this->back; };
	//プレイヤーを捕まえた時のセッターとゲッター
	void Setgetcaught(bool flg) { this->getcaught = flg; };
	bool Getgetcaught() { return this->getcaught; };

	//レイを飛ばす処理
	bool RayLookHit();

	Timer* GetTimer() { return this->time; };

	float GetTime() { return this->Time; };
	float GetTime1() { return this->Time1; };

	void SetTime(float delta) { this->Time = delta; }
	void SetTime1(float delta) { this->Time1 = delta; };

	void Setdeltatime(float delta) { this->deltaTime = delta; };
	float Getdeltatime() { return this->deltaTime; };

	void Getsecurityfov(const std::vector<DirectX::SimpleMath::Vector3>& wanderingPath);
	void securityMove();



};


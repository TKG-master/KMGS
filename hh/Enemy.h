#pragma once
#include <SimpleMath.h>
#include "CShader.h"
#include "Character.h"
#include "Timer.h"
#include "EnemyAI.h"

// セグメント
struct Segment {
	DirectX::SimpleMath::Vector3		startpoint;				// 開始点
	DirectX::SimpleMath::Vector3		endpoint;				// 終了点
};

class EnemyAI;

class Player;

class Enemy : public Character
{
private:

	EnemyAI* AI;

	Timer* time;

	//向いている方向
	DirectX::SimpleMath::Vector3 forward = { 0.0f,0.0f,-1.0f };
	//視野範囲の色
	DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(1.0f, 0.0f, 0.0f, 0.8f);
	//扇形の点の場所
	DirectX::SimpleMath::Vector3 point;
	//次の地点
	DirectX::SimpleMath::Vector3 nextPosition;
	//動く速度
	float MoveSpeed = 1.5f;
	//一番初めにいる場所
	DirectX::SimpleMath::Vector3 StartPosition;
	//視野範囲を描画するために必要な行列
	DirectX::SimpleMath::Matrix rotation;
	//現在の状態を維持する
	EStateType state = EStateType::Patrolling;
	// 経路情報を保持するメンバ変数
	std::vector<DirectX::SimpleMath::Vector3> path;
	int currentPathIndex = 0;
	//徘徊するルートのポイント格納の配列
	std::vector<DirectX::SimpleMath::Vector3> wandering_path;
	int currentwanderingpathIndex = 0;
	//警戒する場合の向き
	std::vector<DirectX::SimpleMath::Vector3> forward_path;
	//次の徘徊の目的地
	DirectX::SimpleMath::Vector3 targetPos;
	// 現在の位置
	DirectX::SimpleMath::Vector3 currentPosition;
	//例のVector3
	DirectX::SimpleMath::Vector3 rayDirection;
	//レーダのどこに自分がいるか
	DirectX::SimpleMath::Vector2 RaderPos;

	//レイを飛ばす高さ
	float StandrayY = 80.0f;
	float SneakrayY = 45.0f;


	//レイがどこまで伸ばして当たったか
	float hitDis = 0.0f;
	//本を読む時間
	float BookReadTime = 0.0f;
	//音が聞こえる範囲
	float hearrange = 0.0f;


	int bookCount = 0;


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
	//本を見つけた時のbool型
	bool RookBook = false;
	//本に夢中になっているとき
	bool bookRead = false;
	//レーダの中にいるのか？
	bool RaderIn = false;
	//巡回か警備か？
	bool TypeSecrity = false;



	float deltaTime = 0.01f;
	float Time1 = 0.0;
	float Time = 0.0f;

	//プレイヤーのデーター（読み取り用）
	const Player* playerdate;

	//扇形を描画するときのセグメント数
	static constexpr int numSegments = 50;
	std::vector<VERTEX_3D> fanVertices = std::vector<VERTEX_3D>(numSegments + 2);

	// 視野角の設定
	float viewAngle = 0.5f; // 視野角
	float viewDistance = 300.0f; // 視野の距離
	bool test = false;
	//視野範囲を描画するときの微調整用のfloat型
	float viewX = 2.0f;
	float viewZ = 2.8f;
	//向いている方向の保持
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

	//移動速度のセット
	void SetMoveSpeed(float num) { this->MoveSpeed = num; };


	//視野範囲の色のゲット
	DirectX::SimpleMath::Color GetColor() const { return color; }
	//扇形の原点
	DirectX::SimpleMath::Vector3 GetPoint() { return fanVertices[0].Position; };

	//見えている奥行をゲット
	float Getview() { return this->viewX; };

	//プレイヤークラスのデータをゲット
	const Player* getPlayer() const {
		return playerdate;
	};

	//ステイとのゲットとセッター
	EStateType GetState() const { return state; };
	void ChangeState(EStateType newState);
	//巡回経路のポイントのゲットとセット
	int GetWaypointIndex() { return this->currentwanderingpathIndex; };
	void SetWaypointIndex(int num) { this->currentwanderingpathIndex = num; };
	//Astarの経路のポイントのゲットとセット
	int GetPathIndex() { return this->currentPathIndex; };
	void SetPathIndex(int num) { this->currentPathIndex = num; };
	//次の巡回ルートのポイント設定
	void NextWaypointIndex() { this->currentwanderingpathIndex++; };
	//ターゲットポスのゲットとセット
	void SetTargetPos(DirectX::SimpleMath::Vector3 pos) { this->targetPos = pos; };
	DirectX::SimpleMath::Vector3 GetTargetPos() { return this->targetPos; };
	//Astarで受け取ったパスのゲット
	std::vector<DirectX::SimpleMath::Vector3> Getpath() { return this->path; };
	//向く方向のゲット
	std::vector<DirectX::SimpleMath::Vector3> Getforwardpath() { return this->forward_path; };

	//スピードのゲット
	float GetMoveSpeed() { return this->MoveSpeed; };



	//AIの初期化
	void EnemyAIInit(int num);

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

	//目線の高さのセッターとゲッター
	void SetStandrayY(float num) { this->StandrayY = num; };
	void SetSneakrayY(float num) { this->SneakrayY = num; };

	void SetState(EStateType newState) { state = newState; };
	//見渡すタイプの敵の位置のゲッターとセッター
	void SetStartPositon(DirectX::SimpleMath::Vector3 Spos) { this->StartPosition = Spos; };
	DirectX::SimpleMath::Vector3 GetStartPositon() { return this->StartPosition; };
	//向いている方向の保持
	DirectX::SimpleMath::Vector3 PositionForward();


	//見えている範囲の描画
	void viewDraw();
	//視野角の計算（座標が入っているか？）
	bool IsInView(DirectX::SimpleMath::Vector3 eyepos, DirectX::SimpleMath::Vector3 lookat, float fov, DirectX::SimpleMath::Vector3 checkpoint, float length);
	//視野角の計算（境界円）
	bool InInViewCircle(DirectX::SimpleMath::Vector3 eyepos, DirectX::SimpleMath::Vector3 lookat, float fov, DirectX::SimpleMath::Vector3 circlecenter, float	radius, float length);
	// 直線と点の距離を求める
	float calcPointLineDist(const DirectX::SimpleMath::Vector3& point, const Segment& segment, DirectX::SimpleMath::Vector3& intersectionpoint, float& t);
	// 線分と直線の長さを求める
	float calcPointSegmentDist(const DirectX::SimpleMath::Vector3& p, const Segment& segment, DirectX::SimpleMath::Vector3& intersectionpoint, float& t);
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

	//徘徊ルートのポイントをゲット
	std::vector<DirectX::SimpleMath::Vector3> GetwanderingPath() { return this->wandering_path; };
	

	//徘徊する関数
	void Wanderaround();

	// 経路に沿って移動するメソッド
	void FollowPath();
	//アニメーションのアップデート
	void AnimUpdate() { 
		if (this->GetAstatus() == WALK)
		{
			this->SetToAnimationName("Walk");
		}
		else if (this->GetAstatus() == IDLE)
		{
			this->SetToAnimationName("Idle");
		}
		Character::Update(); };

	
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
	//本を見つけた時のbool型のゲッターとセッター
	bool GetRookBook() { return this->RookBook; };
	void SetRookBook(bool flg) { this->RookBook = flg; };
	//本を読んでいるときのbool型
	bool GetbookRead() { return this->bookRead; };
	void SetbookRead(bool flg) { this->bookRead = flg; };
	//レーダーの中にいるかどうかのbool型のゲッターとセッター
	bool GetRaderIn() { return this->RaderIn; };
	void SetRaderIn(bool flg) { this->RaderIn = flg; };
	//敵がどっちを警戒しているかのbool型のゲットとセット
	bool Getsecurity() { return this->secrity; };
	void Setsecurity(bool flg) { this->secrity = flg; };

	bool GetTypeSecrity() { return this->TypeSecrity; };

	//レーダー上のポス
	DirectX::SimpleMath::Vector2 GetRaderPos() { return this->RaderPos; };
	void SetRaderPos(DirectX::SimpleMath::Vector2 pos) { this->RaderPos = pos; }

	//レイを飛ばす処理
	bool RayLookHit();
	bool RayLookBook(DirectX::SimpleMath::Vector3 pos,SQUARE3D square);
	//タイマークラスのゲット
	Timer* GetTimer() { return this->time; };
	//タイマーのゲット
	float GetTime() { return this->Time; };
	float GetTime1() { return this->Time1; };
	//タイマーのセット
	void SetTime(float delta) { this->Time = delta; }
	void SetTime1(float delta) { this->Time1 = delta; };
	//イージングに使う値のセットとゲッター
	void Setdeltatime(float delta) { this->deltaTime = delta; };
	float Getdeltatime() { return this->deltaTime; };
	//本を読む時間のゲッターとセッター
	void SetBookReadTime(float ReadTime) { this->BookReadTime = ReadTime; };
	float GetBookReadTime() { return this->BookReadTime; };
	//音が聞こえる範囲
	void Sethearrange(float range) { this->hearrange = range; };
	float Gethearrange() { return this->hearrange; };
	//見渡すタイプの敵の場合の初期化
	void Getsecurityfov(const std::vector<DirectX::SimpleMath::Vector3>& wanderingPath);
	//見渡すパターンの関数
	void securityMove();
	//本を読む回数のゲッターとセッター
	int GetbookCount() { return this->bookCount; };
	void SetbookCount(int num) { this->bookCount = num; };



};


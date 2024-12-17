#include "Player.h"
#include "CScene.h"
#include "BoxObj.h"

void Player::MoveUpdate()
{
	//=== X軸 ===
	//Aが押されていたら
	if (Input::Get()->GetKeyPress(DIK_A))
	{
		//向きを代入
		Velocity.x -= 0.1f;
		if (Velocity.x < -1.0f) { Velocity.x = -1.0f; }

		if (STATUS == IDLE)
			STATUS = WALK;
		else if (STATUS == SNEAK)
			STATUS = SNEAKWLKE;
	}
	else if (Velocity.x < 0.0f) { Velocity.x += 0.025f; }

	if (Input::Get()->GetKeyPress(DIK_D))
	{
		Velocity.x += 0.1f;
		if (Velocity.x > 1) { Velocity.x = 1; }

		if (STATUS == IDLE)
			STATUS = WALK;
		else if (STATUS == SNEAK)
			STATUS = SNEAKWLKE;
	}
	else if (Velocity.x > 0.0f) { Velocity.x -= 0.025f; }


	//=== Z軸 ===
	if (Input::Get()->GetKeyPress(DIK_S))
	{
		Velocity.z -= 0.1f;
		if (Velocity.z < -1.0f) { Velocity.z = -1.0f; }
		
		if (STATUS == IDLE)
			STATUS = WALK;
		else if (STATUS == SNEAK)
			STATUS = SNEAKWLKE;
	}
	else if (Velocity.z < 0.0f) { Velocity.z += 0.025f; }

	if (Input::Get()->GetKeyPress(DIK_W))
	{
		Velocity.z += 0.1f;
		if (Velocity.z > 1) { Velocity.z = 1; }
		

		if (STATUS == IDLE)
			STATUS = WALK;
		else if (STATUS == SNEAK)
			STATUS = SNEAKWLKE;
	}
	else if (Velocity.z > 0.0f) { Velocity.z -= 0.025f; }


	//走るモード
	if (Input::Get()->GetKeyPress(DIK_LSHIFT))
	{
		STATUS = RUN;
	}

	if (Input::Get()->GetKeyTrigger(DIK_E))
	{
		if (STATUS == IDLE)
		{
			STATUS = SNEAK;
		}
		else if (STATUS == SNEAK)
		{
			STATUS = IDLE;
		}
		else if (STATUS == SNEAKWLKE)
		{
			STATUS = WALK;
		}
		else if (STATUS == WALK)
		{
			STATUS = SNEAKWLKE;
		}
		else if (STATUS == RUN)
		{
			STATUS = SNEAKWLKE;
		}
	}



	if (Velocity.x > -0.05f && Velocity.x < 0.05f) { Velocity.x = 0.0f; }
	if (Velocity.z > -0.05f && Velocity.z < 0.05f) { Velocity.z = 0.0f; }

	//ノックの処理
	if (Input::Get()->GetKeyPress(DIK_SPACE))
	{
		if(!this->GetKnockSound() && this->hitBox == true)
		this->SetknockSound(true);
	}



	//VelocityとMoveSpeedをかけて入れる
	if (STATUS == WALK) {
		m_AnimationObject.m_Position += Velocity * MoveSpeed;
		this->SetknockSound(false);
		SetToAnimationName("Walk");
	}
	else if (STATUS == RUN) {
		m_AnimationObject.m_Position += Velocity * (MoveSpeed * 2.5);
		this->SetknockSound(true);
		SetToAnimationName("Run");
		if (this->GetAnimEndState())
		{
			this->Stand = true;
		}

	}
	else if (STATUS == SNEAKWLKE)
	{
		m_AnimationObject.m_Position += Velocity * MoveSpeed * 0.5f;
		this->SetknockSound(false);
		SetToAnimationName("SWalk");
	}
	//----------------------//

	if (Velocity.Length() < 0.5f && STATUS != SNEAK && STATUS != SNEAKWLKE && STATUS != GOAL)
	{
		STATUS = IDLE;
		SetToAnimationName("Idle");
		if (this->GetAnimEndState())
		{
			this->Stand = true;
		}

	}
	else if (Velocity.Length() < 0.5f && STATUS == SNEAK)
	{
		STATUS = SNEAK;
		SetToAnimationName("Spose");
	}
	else if (Velocity.Length() < 0.5f && STATUS == SNEAKWLKE)
	{
		STATUS = SNEAK;
		SetToAnimationName("Spose");
	}
	else if (Velocity.Length() < 0.5f && STATUS == GOAL)
	{
		SetToAnimationName("Goal");
	}

	if (STATUS == GOAL)
	{
		this->SetAnimationSpeed(0.5f);
	}
	else
	{
		this->SetAnimationSpeed(1.0f);
	}


	//=== 回転の処理 ===
	DirectX::SimpleMath::Vector3 velo = Velocity;
	float length = velo.Length();

	// 一定の速度がある場合のみ回転を更新
	if (length > 0.01f) {
		velo.Normalize();
		float angle = DirectX::XMConvertToDegrees(atan2(-velo.x, -velo.z));

		// 角度を0から360度に変換
		if (angle < 0) {
			angle += 360.0f;
		}

		m_AnimationObject.m_Rotation.y = angle;
	}
	ModifyRotation();

}

void Player::Init(
	std::string ModelName, std::string TexFolderPath,
	std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader)
{
		//モデル読み込み等
	Character::Init(ModelName, TexFolderPath, MotionName, vShader, pShader);
	STATUS = IDLE;
	this->square.type = ObjectType::PLAYER;
}

Player::Player(std::string ModelName, std::string TexFolderPath,
	std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader)
{
	//モデル読み込み等
	Character::Init(ModelName, TexFolderPath, MotionName, vShader, pShader);
	STATUS = IDLE;
	this->square.type = ObjectType::PLAYER;
}

Player::~Player()
{

}


void Player::UnInit()
{
	Character::UnInit();
}

void Player::StickyWall(CORRECT_DIR dir)
{
	// 壁に張り付く方向に応じて処理を実行
	if (dir.x == 1) {
		// 右方向に張り付く処理
		this->SetRotation(Vector3(0.0f, 270.0f, 0.0f));
		//張り付き状態
		this->SetSticking(true);
		STATUS = IDLE;
	}
	else if (dir.x == -1) {
		// 左方向に張り付く処理
		this->SetRotation(Vector3(0.0f, 90.0f, 0.0f));
		//張り付き状態
		this->SetSticking(true);
		STATUS = IDLE;

	}

	if (dir.z == 1 && Input::Get()->GetKeyPress(DIK_S)) {
		// 上方向に張り付く処理
		this->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
		//張り付き状態
		this->SetSticking(true);
		STATUS = IDLE;
	}
	else if (dir.z == -1 && Input::Get()->GetKeyPress(DIK_W)) {
		// 下方向に張り付く処理
		this->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
		//張り付き状態
		this->SetSticking(true);
		STATUS = IDLE;
	}
}

void Player::Update()
{

	// 移動処理
	MoveUpdate();
	// アニメーション
	AnimUpdate();

	this->hitBox = false;

	//当たり判定の押し出し処理
	for (auto it = CScene::BOXS.begin(); it != CScene::BOXS.end(); it++)
	{
		BoxObj* box = *it;
		//当たり判定---------------------------------//
		if (CCollision::Square3DCollision(this->square, box->square))
		{
			prevFrameCorrect = CCollision::ResolveCollision(this->square, box->square);
			this->squareUpdate();
			this->hitBox = true;
		}
	}

	//しゃがみ状態と立ち状態の当たり判定の変更
	if (STATUS == SNEAK || STATUS == SNEAKWLKE)
	{
		this->SetSquare3D(Vector3(45.0f, 40.0f, 45.0f));
		this->SetPosition(Vector3(this->GetPosition().x, 0.0f, this->GetPosition().z));
	}
	else if (STATUS != SNEAK && STATUS != SNEAKWLKE && this->Stand == true)
	{
		this->SetSquare3D(Vector3(45.0f, 80.0f, 45.0f));
		this->SetPosition(Vector3(this->GetPosition().x, 0.1f, this->GetPosition().z));
	}

}

void Player::Draw()
{
	Character::Draw();
}

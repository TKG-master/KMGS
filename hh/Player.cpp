#include "Player.h"
#include "CScene.h"
#include "BoxObj.h"

void Player::MoveUpdate()
{
	//=== X�� ===
	//A��������Ă�����
	if (Input::Get()->GetKeyPress(DIK_A))
	{
		//��������
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


	//=== Z�� ===
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


	//���郂�[�h
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

	//�m�b�N�̏���
	if (Input::Get()->GetKeyPress(DIK_SPACE))
	{
		if(!this->GetKnockSound() && this->hitBox == true)
		this->SetknockSound(true);
	}



	//Velocity��MoveSpeed�������ē����
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


	//=== ��]�̏��� ===
	DirectX::SimpleMath::Vector3 velo = Velocity;
	float length = velo.Length();

	// ���̑��x������ꍇ�̂݉�]���X�V
	if (length > 0.01f) {
		velo.Normalize();
		float angle = DirectX::XMConvertToDegrees(atan2(-velo.x, -velo.z));

		// �p�x��0����360�x�ɕϊ�
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
		//���f���ǂݍ��ݓ�
	Character::Init(ModelName, TexFolderPath, MotionName, vShader, pShader);
	STATUS = IDLE;
	this->square.type = ObjectType::PLAYER;
}

Player::Player(std::string ModelName, std::string TexFolderPath,
	std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader)
{
	//���f���ǂݍ��ݓ�
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
	// �ǂɒ���t�������ɉ����ď��������s
	if (dir.x == 1) {
		// �E�����ɒ���t������
		this->SetRotation(Vector3(0.0f, 270.0f, 0.0f));
		//����t�����
		this->SetSticking(true);
		STATUS = IDLE;
	}
	else if (dir.x == -1) {
		// �������ɒ���t������
		this->SetRotation(Vector3(0.0f, 90.0f, 0.0f));
		//����t�����
		this->SetSticking(true);
		STATUS = IDLE;

	}

	if (dir.z == 1 && Input::Get()->GetKeyPress(DIK_S)) {
		// ������ɒ���t������
		this->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
		//����t�����
		this->SetSticking(true);
		STATUS = IDLE;
	}
	else if (dir.z == -1 && Input::Get()->GetKeyPress(DIK_W)) {
		// �������ɒ���t������
		this->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
		//����t�����
		this->SetSticking(true);
		STATUS = IDLE;
	}
}

void Player::Update()
{

	// �ړ�����
	MoveUpdate();
	// �A�j���[�V����
	AnimUpdate();

	this->hitBox = false;

	//�����蔻��̉����o������
	for (auto it = CScene::BOXS.begin(); it != CScene::BOXS.end(); it++)
	{
		BoxObj* box = *it;
		//�����蔻��---------------------------------//
		if (CCollision::Square3DCollision(this->square, box->square))
		{
			prevFrameCorrect = CCollision::ResolveCollision(this->square, box->square);
			this->squareUpdate();
			this->hitBox = true;
		}
	}

	//���Ⴊ�ݏ�ԂƗ�����Ԃ̓����蔻��̕ύX
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

#include "Enemy.h"
#include "CBoxMesh.h"
#include "Player.h"
#include "CScene.h"
#include "BoxObj.h"
#include "CSceneManager.h"

using namespace DirectX::SimpleMath;



void Enemy::Init(std::string ModelName, std::string TexFolderPath, std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader)
{
    //���f���ǂݍ��ݓ�
    Character::Init(ModelName, TexFolderPath, MotionName, vShader, pShader);
    this->DrawInit();
    STATUS = IDLE;
    this->square.type = ObjectType::ENEMY;
}

Enemy::Enemy(std::string ModelName, std::string TexFolderPath, std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader, const Player* Pl)
{
    //���f���ǂݍ��ݓ�
    Character::Init(ModelName, TexFolderPath, MotionName, vShader, pShader);
    this->DrawInit();
    STATUS = IDLE;
    this->playerdate = Pl;
    this->square.type = ObjectType::ENEMY;
    time = new Timer();
    this->Setgetcaught(false);
    this->SethearSound(false);
    this->Setback(false);
    this->SetSearch(false);
}

Enemy::~Enemy()
{
    delete time;
}

void Enemy::DrawInit()
{

    e_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");

    MATERIAL	emtrl;
    emtrl.Ambient = Color(0, 0, 0, 0);
    emtrl.Diffuse = Color(1, 1, 1, 1);
    emtrl.Emission = Color(0, 0, 0, 0);
    emtrl.Specular = Color(0, 0, 0, 0);
    emtrl.TextureEnable = TRUE;

    e_Material.Create(emtrl);


    // �e�N�X�`���̓ǂݍ���
    bool sts = e_Texture.Load("assets\\siro.jpg");
    assert(sts == true);
}

void Enemy::Update()
{
    //�G�̓����̃A�b�v�f�[�g
    MoveUpdate();

    // �A�j���[�V�����̃A�b�v�f�[�g
    AnimUpdate();
    //�����蔻��̉����o������
    for (auto it = CScene::BOXS.begin(); it != CScene::BOXS.end(); it++)
    {
        BoxObj* box = *it;
        //�����蔻��---------------------------------//
        if (CCollision::Square3DCollision(this->square, box->square))
        {
            //�����蔻��̕⊮
            CCollision::ResolveCollision(this->square, box->square);
            this->squareUpdate();
        }
    }

    if (CCollision::Square3DCollision(this->square, playerdate->square))
    {
        this->Setgetcaught(true);
    }

}

void Enemy::MoveUpdate()
{
    
    switch (this->GetState())
    {
    case EStateType::Patrolling:
        this->PatrollingMove();
        break;
    case EStateType::Investigating:
        this->InvestigatingMove();
        break;
    case EStateType::Alerted:
        this->AlertedMove();
        break;
    }
     //�i�s�����Ɋ�Â��ĉ�]������
    UpdateRotation();

}

void Enemy::Draw()
{
    this->EnemyDraw();
    this->viewDraw();
}

DirectX::SimpleMath::Vector3 Enemy::PositionForward()
{
    this->SaveForward.x = this->GetPosition().x + (this->Getforward().x * 0.0001f);
    this->SaveForward.z = this->GetPosition().z + (this->Getforward().z * 0.0001f);

    return this->SaveForward;
}

//�G�̌����Ă���͈͂̕`��
void Enemy::viewDraw()
{
    ID3D11DeviceContext* deviceContext = Renderer::GetDeviceContext();

    // �g�|���W�[���Z�b�g�i���v���~�e�B�u�^�C�v�j
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // ���S�_�̐ݒ�
    //��`�̌��_��G�̃|�W�V�����Ɏw��
    fanVertices[0].Position = this->GetPosition() + (this->GetPosition() * -1);
    //��`�ɂȂ�̐F��t���邩�̎w��
    DirectX::SimpleMath::Color fanColor(color);
    fanVertices[0].Diffuse = fanColor;


    //��`�̊e�Z�O�����g�̈ʒu���v�Z
    for (int i = 0; i <= numSegments; ++i)
    {

        float angle = -viewAngle / 2 + viewAngle * i / numSegments;

        //�P�Z�O�����g�̓_�̂����Ƃ����̌v�Z
        float x = cos(angle) * viewDistance * this->Getview();
        float z = sin(angle) * viewDistance * this->Getview();

        //��`��������Ȃ��悤��y����+0.1f
        point = DirectX::SimpleMath::Vector3(x, 0.0f, z);

        // �G�l�~�[�̌����ɉ����ĉ�]
        rotation = DirectX::SimpleMath::Matrix::CreateRotationY(atan2(90.0f, 0.0f));
        point = DirectX::SimpleMath::Vector3::Transform(point, rotation);

        // �G�l�~�[�̈ʒu����Ɉړ�
        point += this->GetPosition() + (this->GetPosition() * -1);

        //�O�͌��_������i�Ƀv���X�P
        fanVertices[i + 1].Position = point;
        fanVertices[i + 1].Diffuse = fanColor;

    }

    //�C���f�b�N�X�ɓo�^
    std::vector<unsigned int> fanIndices;
    for (int i = 1; i < numSegments + 1; ++i)
    {
        fanIndices.push_back(0);
        fanIndices.push_back(i + 1);
        fanIndices.push_back(i);
    }

    // ���_�o�b�t�@���쐬���Đݒ�
    e_VertexBuffer.Create(fanVertices);
    e_VertexBuffer.SetGPU();

    // �C���f�b�N�X�o�b�t�@���쐬���Đݒ�
    e_IndexBuffer.Create(fanIndices);
    e_IndexBuffer.SetGPU();

    //�V�F�[�_�[�̐ݒ�
    e_Shader.SetGPU();

    e_Material.SetGPU();
    //�e�N�X�`���̐ݒ�
    e_Texture.SetGPU();

    // �g�|���W�[���O�p�`���X�g�ɐݒ肵�ĕ`��
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext->DrawIndexed(fanIndices.size(), 0, 0);

}
//�G�̎���͈͂Ƀv���C���[�������Ă邩�̔���
bool Enemy::IsInView(DirectX::SimpleMath::Vector3 eyepos, DirectX::SimpleMath::Vector3 lookat, float fov, DirectX::SimpleMath::Vector3 checkpoint, float length)
{
    //���������ׂĂO�̎��ɂǂ��������ĂȂ�����
    if (lookat.x == 0 && lookat.z == 0 && lookat.y == 0)
    {
        return false;
    }
    // �`�F�b�N�ΏۂƎ��_�����ԃx�N�g�����v�Z
    DirectX::SimpleMath::Vector3 vecobj;
    vecobj = checkpoint - eyepos;
    // �I�u�W�F�N�g�Ƃ̋��������߂�
    float objlength = vecobj.Length();
    // �����͈͊O�Ȃ�false
    if (objlength > length) {
        test = false;
        return false;
    }
    // �����x�N�g��
    DirectX::SimpleMath::Vector3 vecview;
    vecview = lookat - eyepos;
    // ���K��
    vecview.Normalize();
    vecobj.Normalize();
    // ���ς��v�Z
    float dotobj = vecview.Dot(vecobj);
    //// ��]
    DirectX::SimpleMath::Matrix mtx;

    mtx = mtx.CreateRotationX(fov / 2.0f) * mtx.CreateRotationZ(fov / 2.0f) * mtx.CreateRotationY(fov / 2.0f);

    DirectX::SimpleMath::Vector3 vecrotview;
    vecrotview = vecview.Transform(vecview, mtx);
    // ���ς��v�Z
    float dotrotview = vecview.Dot(vecrotview);
    // ����p�͈͓��H
    if (dotrotview <= dotobj) {
        return true;
    }
    else {
        return false;
    }

}
//�G�̌����Ă�������ƃ��f���̌��������킹��
void Enemy::UpdateRotation()
{

    DirectX::SimpleMath::Vector3 forw = this->Getforward();
    float angle = DirectX::XMConvertToDegrees(atan2(-forw.x, -forw.z));

    if (angle < 0) {
        angle += 360.0f;
    }

    m_AnimationObject.m_Rotation.y = angle;

    ModifyRotation();

}

//�G���v���C���[�������Ă��Ȃ����̓���
void Enemy::PatrollingMove()
{
    if (STATUS == WALK)
    {
        SetToAnimationName("Walk");
    }
    else if (STATUS != WALK)
    {
        STATUS = WALK;
    }

    //�p�j���[�h
    if (!this->GetSearch() && !this->back)
    {
        this->Wanderaround();
    }
    //�T���ɍs���Ă���
    else if (this->GetSearch())
    {
        this->FollowPath();
    }
    else if (this->back)
    {
        this->FollowPath();
    }


}

void Enemy::AlertedMove()
{

    // �o�H�ɉ����Ĉړ�
    this->FollowPath();

    if (STATUS == RUN)
    {
        SetToAnimationName("Run");
    }
    else if (STATUS != RUN)
    {
        STATUS = RUN;
    }

}

void Enemy::InvestigatingMove()
{
}

void Enemy::SetPath(const std::vector<DirectX::SimpleMath::Vector3>& newPath)
{
    path = newPath;
    currentPathIndex = 1;  // �o�H�̍ŏ��̒n�_����J�n
}

void Enemy::SetwanderingPath(const std::vector<DirectX::SimpleMath::Vector3>& wanderingPath)
{
    wandering_path = wanderingPath;
}

void Enemy::Wanderaround()
{
    if (currentwanderingpathIndex >= wandering_path.size())
    {
        currentwanderingpathIndex = 0;
    }

    // ���̈ʒu
    DirectX::SimpleMath::Vector3 targetPos = wandering_path[currentwanderingpathIndex];

    // ���݂̈ʒu
    DirectX::SimpleMath::Vector3 currentPosition = this->GetPosition();

    // �ړ��ʂ��v�Z
    DirectX::SimpleMath::Vector3 direction = targetPos - currentPosition;
    float distance = direction.Length();

    // ���̈ʒu�ɓ��B�����ꍇ�̔�����ɂ߂�
    float tolerance = MoveSpeed * 2.5f;
    if (distance < tolerance) {
        // ���̈ʒu�ɓ��B�����ꍇ
        this->SetPosition(targetPos);
        currentwanderingpathIndex++;
    }
    else {
        // �ړ��ʂ𐳋K�����đ��x���|����
        direction.Normalize();
        this->SetPosition(currentPosition + direction * MoveSpeed);
    }

    // �i�s�����Ɍ����ĉ�]���X�V
    if (direction.LengthSquared() > 0.0f) {
        //�������Z�b�g
        this->Setforward(direction);
        UpdateRotation();  // ��]�̍X�V
    }

}

void Enemy::FollowPath()
{
    // �o�H���Ȃ����A���łɌo�H�̏I�_�ɓ��B���Ă���ꍇ
    if (path.empty() || currentPathIndex >= path.size()) {
        //�T�����[�h���I�������
        if (this->GetSearch())
        {
            this->SetSearch(false);
            this->SethearSound(false);
            this->back = true;
            return;
        }
        //�p�j���[�g�ɖ߂�����
        else if(this->back)
        {
            this->back = false;
            currentwanderingpathIndex = 0;
            return;
        }
        else
        {
            return;
        }
    }

    // ���̈ʒu
    DirectX::SimpleMath::Vector3 targetPos = path[currentPathIndex];

    // ���݂̈ʒu
    DirectX::SimpleMath::Vector3 currentPosition = this->GetPosition();

    // �ړ��ʂ��v�Z
    DirectX::SimpleMath::Vector3 direction = targetPos - currentPosition;
    float distance = direction.Length();

    // ���̈ʒu�ɓ��B�����ꍇ�̔�����ɂ߂�
    float tolerance = MoveSpeed * 2.5f;
    if (distance < tolerance) {
        // ���̈ʒu�ɓ��B�����ꍇ
        this->SetPosition(targetPos);
        currentPathIndex++;
    }
    else {
        // �ړ��ʂ𐳋K�����đ��x���|����
        direction.Normalize();
        this->SetPosition(currentPosition + direction * MoveSpeed * 1.5f);
    }

    // �i�s�����Ɍ����ĉ�]���X�V
    if (direction.LengthSquared() > 0.0f) {
        //�������Z�b�g
        this->Setforward(direction);
        UpdateRotation();  // ��]�̍X�V
    }
}



void Enemy::LookAround()
{
    // ���݂̌����Ă�������iforward�j���擾
    DirectX::SimpleMath::Vector3 currentForward = this->Getforward();

    // Y������̉�]�p�x
    float angle = atan2(currentForward.z, currentForward.x);

    // �E�Ɍ������Ă��邩�A���Ɍ������Ă��邩�𔻒�
    if (isLookingRight) {
        angle += lookSpeed; // �E�Ɍ������Ċp�x�𑝉�������
        if (angle >= maxLookAngle) {
            isLookingRight = false; // �ő�p�x�ɒB�����獶�ɉ�]����
        }
    }
    else {
        angle -= lookSpeed; // ���Ɍ������Ċp�x������������
        if (angle <= -maxLookAngle) {
            isLookingRight = true; // �ŏ��p�x�ɒB������E�ɉ�]����
        }
    }

    // �V����forward�x�N�g�����v�Z
    DirectX::SimpleMath::Vector3 newForward;
    newForward.x = cos(angle); // x������cos���g���ĉ�]
    newForward.z = sin(angle); // z������sin���g���ĉ�]

    // �V����������ݒ�
    this->Setforward(newForward);

    // ��]��̌����ŃL�����N�^�[�̉�]���X�V
    UpdateRotation();
}












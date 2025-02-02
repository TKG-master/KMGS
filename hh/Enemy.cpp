#include "Enemy.h"
#include "CBoxMesh.h"
#include "Player.h"
#include "CScene.h"
#include "BoxObj.h"
#include "GameUI.h"
#include "Camera.h"
#include "easings.h"
#include <algorithm>
#include <iostream>

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
    time = new Timer(true);


    this->Setgetcaught(false);
    this->SethearSound(false);
    this->Setback(false);
    this->SetSearch(false);

}

Enemy::~Enemy()
{
    delete time;
    time = nullptr;

    delete AI;
    AI = nullptr;

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
    bool sts = e_Texture.Load("assets\\Texture\\siro.jpg");
    assert(sts == true);
}

void Enemy::Update()
{
    // �A�j���[�V�����̃A�b�v�f�[�g
    AnimUpdate();

    //�G�̓����̃A�b�v�f�[�g
    MoveUpdate();


    //�����蔻��̉����o������
    for (auto it = CScene::BOXS.begin(); it != CScene::BOXS.end(); it++)
    {
        BoxObj* box = *it;
        //�����蔻��---------------------------------//
        if (box->square.type == ObjectType::BOX)
        {
            if (CCollision::Square3DCollision(this->square, box->square))
            {
                //�����蔻��̕⊮
                CCollision::ResolveCollision(this->square, box->square);
                this->squareUpdate();
            }
        }
    }

    //�i�s�����Ɋ�Â��ĉ�]������
    UpdateRotation();

}

void Enemy::MoveUpdate()
{
    AI->Update(this);
}

void Enemy::Draw()
{
    this->EnemyDraw();
    this->viewDraw();

}

void Enemy::ChangeState(EStateType newState)
{
    if (state != newState) {
        state = newState;
        AI->SetState(newState);
    }
}

void Enemy::EnemyAIInit(int num)
{
    AI = new EnemyAI(num);
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
    if (!this->GetbookRead())
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
            float z = sin(angle) * viewDistance * viewZ;

            //��`��������Ȃ��悤��y����+0.1f
            point = DirectX::SimpleMath::Vector3(x, 0.1f, z);

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

        if (this->GetState() == EStateType::Serch)
        {
            this->SetColor(Color(1.0f, 0.0f, 0.0f, 0.8f));
        }
        else
        {
            this->SetColor(Color(1.0f, 1.0f, 0.0f, 0.8f));
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
        //this->test = false;
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
//���E�~�̔���
bool Enemy::InInViewCircle(DirectX::SimpleMath::Vector3 eyepos, DirectX::SimpleMath::Vector3 lookat, float fov, DirectX::SimpleMath::Vector3 circlecenter, float radius, float length)
{
    // ���������ׂ�0�̂Ƃ��͂ǂ��������Ă��Ȃ��Ƃ݂Ȃ�
    if (lookat.x == 0 && lookat.z == 0 && lookat.y == 0) {
        return false;
    }

    bool sts = true;


    // �`�F�b�N�ΏۂƎ��_�����ԃx�N�g��
    Vector3 vecobj;
    vecobj = circlecenter - eyepos;
    // �I�u�W�F�N�g�Ƃ̋��������߂�
    float objlength = vecobj.Length();
    // �����͈͊O�H
    if (objlength - radius > length) {
        return false;
    }
    // ����̏���x�N�g�������߂�
    // ��]
    Matrix mtx;
    mtx = mtx.CreateRotationY(fov / 2.0f);// ����p�̔������w�肵�čs����쐬
    Vector3 lookatplus;
    Vector3 lookatminus;

    // �����x�N�g��
    Vector3 v;
    v = lookat - eyepos;
    lookatplus = v.Transform(v, mtx);// �����x�N�g��������p�̔��� ��]������
    lookatplus += eyepos;
    // ����̉����x�N�g�������߂�
    mtx = mtx.CreateRotationY(-fov / 2.0f);// ����p�̔������w�肵�čs����쐬
    lookatminus = v.Transform(v, mtx);// �����x�N�g��������p�̔��� ��]������
    lookatminus += eyepos;
    // ����x�N�g���Ɠ_�̋��������߂�
    {
        Segment s;
        Vector3 intersectionpoint;
        float t = 0.0f;
        float distance = 0.0f;
        s.startpoint = eyepos;
        s.endpoint = lookatplus;
        distance = calcPointSegmentDist(circlecenter, s, intersectionpoint, t);
        if (distance < radius) {
            return true;
        }
    }

    // �����x�N�g���Ɠ_�̋��������߂�
    {
        Segment s;
        Vector3 intersectionpoint;
        float t = 0.0f;
        float distance = 0.0f;
        s.startpoint = eyepos;
        s.endpoint = lookatminus;
        distance = calcPointSegmentDist(circlecenter, s, intersectionpoint, t);
        if (distance < radius) {
            return true;
        }
    }
    // ���S���W������͈͓����H ���`�F�b�N����
    sts = IsInView(eyepos,lookat,fov,circlecenter,length);

    return sts;
}

float Enemy::calcPointLineDist(const DirectX::SimpleMath::Vector3& point, const Segment& segment, DirectX::SimpleMath::Vector3& intersectionpoint, float& t)
{
    float distance = 0.0f;

    //�����̃x�N�g��
    double ABx = segment.endpoint.x - segment.startpoint.x;
    double ABy = segment.endpoint.y - segment.startpoint.y;
    double ABz = segment.endpoint.z - segment.startpoint.z;


    //�����̎��_�Ɠ_�����ԃx�N�g��
    double APx = point.x - segment.startpoint.x;
    double APy = point.y - segment.startpoint.y;
    double APz = point.z - segment.startpoint.z;

    //����AB�̒��������߂�
    double AB2 = ABx * ABx + ABy * ABy + ABz * ABz;

    double ABdotAP = ABx * APx + ABy * APy + ABz * APz;

    //AB�x�N�g����AP�x�N�g���̓��ς��v�Z
    double tt = ABdotAP / AB2;

    //�����̑�
    intersectionpoint.x = static_cast<float>(segment.startpoint.x + ABx * tt);
    intersectionpoint.y = static_cast<float>(segment.startpoint.y + ABy * tt);
    intersectionpoint.z = static_cast<float>(segment.startpoint.z + ABz * tt);

    t = static_cast<float>(tt);

    //�����̑��̒���
    distance = (intersectionpoint - point).Length();

    return distance;
}

float Enemy::calcPointSegmentDist(const DirectX::SimpleMath::Vector3& p, const Segment& segment, DirectX::SimpleMath::Vector3& intersectionpoint, float& t)
{
    float distance = calcPointLineDist(p, segment, intersectionpoint, t);

    // ��_�������̊O�ɂ���i�n�_�ɋ߂��j
    if (t < 0.0f) {

        intersectionpoint = segment.startpoint;		// �J�n�_����_

        float l = (p - intersectionpoint).Length();	// ��_�Ƃ̋��������߂�

        return l;
    }

    // ��_�������̊O�ɂ���i�I�_�ɋ߂��j
    if (t > 1.0f) {

        intersectionpoint = segment.endpoint;		// �I�_����_

        float l = (p - intersectionpoint).Length();	// ��_�Ƃ̋��������߂�

        return l;
    }

    // ��_��������ɂ���i�O�������P�j
    return distance;
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

void Enemy::lookaround()
{
        // �^�C�}�[���܂��J�n����Ă��Ȃ��ꍇ�ɊJ�n����
        if (!time->IsRunning()) {
            time->StartCountDown(1.5f);
        }
        if (STATUS != IDLE)
        {
            STATUS = IDLE;
        }
        else if (STATUS == IDLE)
        {
            SetToAnimationName("Idle");
        }
        if (time->IsTimeUp())
        {
            time->Reset();
            if (currentwanderingpathIndex >= wandering_path.size())
            {
                currentwanderingpathIndex = 0;
            }

            targetPos = wandering_path[currentwanderingpathIndex];

            this->SetState(EStateType::Turn);
        }
}

void Enemy::InvestigatingMove()
{
    this->Setforward(EaseInCirc(this->Getforward(),Vector3(0.0f,0.0f,-1.0f), Time));
    Time += deltaTime;
    if (Time >= 1.0f) {
        Time = 0.5f;
        this->SetState(EStateType::Patrolling);
    }
}

void Enemy::SetPath(const std::vector<DirectX::SimpleMath::Vector3>& newPath)
{
    path = newPath;
    currentPathIndex = 1;  // �o�H�̍ŏ��̒n�_����J�n
}

void Enemy::SetwanderingPath(const std::vector<DirectX::SimpleMath::Vector3>& wanderingPath)
{
    wandering_path = wanderingPath;
    currentwanderingpathIndex = 1;
}

void Enemy::Wanderaround()
{

    // ���̈ʒu
    targetPos = wandering_path[currentwanderingpathIndex];

    // ���݂̈ʒu
    currentPosition = this->GetPosition();

    // �ړ��ʂ��v�Z
    DirectX::SimpleMath::Vector3 direction = targetPos - currentPosition;
    float distance = direction.Length();

    // ���̈ʒu�ɓ��B�����ꍇ�̔�����ɂ߂�
    float tolerance = MoveSpeed * 2.5f;
    if (distance < tolerance) {
        // ���̈ʒu�ɓ��B�����ꍇ
        this->SetPosition(targetPos);
        currentwanderingpathIndex++;
        //this->SetState(EStateType::Lookaround);
    }
    else {
        // �ړ��ʂ𐳋K�����đ��x���|����
        direction.Normalize();
        this->SetPosition(currentPosition + direction * MoveSpeed);
    }

     //�i�s�����Ɍ����ĉ�]���X�V
    if (direction.LengthSquared() > 0.0f) {
        DirectX::SimpleMath::Vector3 currentForward = this->Getforward();
        DirectX::SimpleMath::Vector3 newForward = EaseInCirc(currentForward, direction, Time1);
        this->Setforward(newForward);
        Time1 += deltaTime;
        if (Time1 >= 1.0f) {
            Time1 = 0.0f;
        }
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
            this->time->Reset();
            return;
        }
        else if (this->GetRookBook())
        {
            this->bookCount++;
            this->time->Reset();
            this->SetRookBook(false);
            this->SethearSound(false);
            this->bookRead = true;
          return;
        }
        //�p�j���[�g�ɖ߂�����
        if(this->back)
        {
            if (this->GetState() == EStateType::Fixed)
            {
                this->back = false;
                currentwanderingpathIndex = 0;
                return;
            }
            else
            {
                this->SetState(EStateType::Patrolling);
                this->back = false;
                currentwanderingpathIndex = 0;
                return;
            }
        }
        else
        {
            return;
        }
    }
    else {
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
}

bool Enemy::RayLookHit()
{
    // �v���C���[�Ɍ������ă��C���΂�
    rayDirection = playerdate->GetPosition() - this->GetPosition();
    Vector3 Epos = this->GetPosition();
    // ���C�̔��ˈʒu��Y�������ɏ�����������
    if (playerdate->GetStand())
    {
        Epos.y += StandrayY;
    }
    else if (!playerdate->GetStand())
    {
        Epos.y += SneakrayY;
    }
    //���K��
    rayDirection.Normalize();
    if (CCollision::RayIntersectsBox(Epos, rayDirection, playerdate->square,CScene::BOXS, hitDis)) {
        this->SetSearch(true);
        return true;
    }
    return false;
}

bool Enemy::RayLookBook(DirectX::SimpleMath::Vector3 pos,SQUARE3D square)
{
    // �v���C���[�Ɍ������ă��C���΂�
    rayDirection = pos - this->GetPosition();
    Vector3 Epos = this->GetPosition();
    // ���C�̔��ˈʒu��Y�������ɏ�����������
    Epos.y += 45.0f;
    //���K��
    rayDirection.Normalize();
    if (CCollision::RayIntersectsBox(Epos, rayDirection,square,CScene::BOXS, hitDis)) {
        this->SetRookBook(true);
        return true;
    }
    return false;
}

void Enemy::Getsecurityfov(const std::vector<DirectX::SimpleMath::Vector3>& forvPath)
{
    this->SetState(EStateType::Fixed);
    this->TypeSecrity = true;
    this->SetStartPositon(this->GetPosition());
    forward_path = forvPath;
}

void Enemy::securityMove()
{

    if (!time->IsRunning()) {
        time->StartCountDown(0.5f);
    }

    if (time->IsTimeUp())
    {
        if (!this->secrity)
        {
            this->Setforward(EaselnQuart(forward_path[0], forward_path[1], Time));
            Time += deltaTime;
            if (Time >= 1.0f) {
                Time = 0.0f;
                time->Reset();
                this->secrity = true;
            }
        }
        else if (this->secrity)
        {
            this->Setforward(EaselnQuart(forward_path[1], forward_path[0], Time));
            Time += deltaTime;
            if (Time >= 1.0f) {
                Time = 0.0f;
                time->Reset();
                this->secrity = false;
            }
        }
    }
}

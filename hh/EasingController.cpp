#include "EasingController.h"
#include "Camera.h"
#include "Enemy.h"
#include "easings.h"
#include "Player.h"
#include "GoalObj.h"
#include "BoxObj.h"
#include "CSceneManager.h"
#include "GameUI.h"

using namespace DirectX::SimpleMath;

EasingController::EasingController()
{
    Rookfarst = false;
    Goal = false;
    EndEasing = true;
    Fadein = true;
    Fadeout = true;
    ClearUIEasingX = true;
    ClearUIEasingY = true;
    ImageUIEasing = true;
    ImageEasingEnd = true;

}

EasingController::~EasingController()
{

}

bool EasingController::farstEasing(Camera* camera, Player* Pl, GoalObj* goal)
{
    //�S�[���̃|�W�V����
    DirectX::SimpleMath::Vector3 goalpos = goal->GetPosition();
    goalpos.y += 775.0f;
    goalpos.z += -200.0f;
    //�v���C���[�̃|�W�V����
    DirectX::SimpleMath::Vector3 plpos = Pl->GetPosition();
    plpos.y += 700.0f;
    plpos.z += -200.0f;
    //�ڐ��̍��W
    //�S�[��
    DirectX::SimpleMath::Vector3 goalFoucusPos;
    goalFoucusPos = goal->GetPosition();
    //�v���C���[
    DirectX::SimpleMath::Vector3 plFoucusPos;
    plFoucusPos = Pl->GetPosition();
    if (startEasing) {
        if (isEasingStart)
        {
            //�|�W�V�����̃C�[�W���O
            camera->SetPosition(EaselnOutBack(goalpos, plpos, EasingStartTime));
            //�ڐ��̃C�[�W���O
            camera->SetFoucus(EaselnOutBack(goalFoucusPos, plFoucusPos, EasingStartTime));
            EasingStartTime += deltaTime;
            if (EasingStartTime >= 1.0f) {
                EasingStartTime = 0.0f;
                isEasingStart = false;
                return true;
            }
        }
    }
    return false;
}

bool EasingController::EnemyEasing(std::vector<Enemy*> enemys, DirectX::SimpleMath::Vector3 PlPos, Camera* camera, Timer* timer)
{

    if (!enemys.empty() && this->RookEasing == true)
    {
        Enemy* enemy = enemys[0]; // �ŏ��Ɍ������G���g�p�i��������ꍇ�̑Ώ��͕K�v�ɉ����āj
        Vector3 enemyPosition = enemy->GetPosition();
        Vector3 enemyPositionFoucus = enemyPosition;
        Vector3 playerPositionFoucus = PlPos;
        Vector3 playerPosition = PlPos;
        enemyPositionFoucus.y += 500.0f;
        enemyPositionFoucus.z += -200.0f;

        enemyPosition.y += 50.0f;
        //�G�Ɍ����������Ɍ������G�ɑ΂��ăJ�����̃C�[�W���O
        if (!timer->IsRunning())
        {
            camera->SetPosition(EaseOutCirc(camera->GetCamPosition(), enemyPositionFoucus, EnemyTime));
            camera->SetFoucus(EaseOutCirc(camera->GetCamforcas(), enemyPosition, EnemyTime));
            EnemyTime += deltaTime;
            if (EnemyTime >= 1.0f) {
                EnemyTime = 0.0f;
                RookEasing = false;
                return true;
            }
        }
//        return false;
    }
    return false;
}

void EasingController::farstBoxEasing(std::vector<BoxObj*> boxs)
{
    // �C�[�W���O�̊J�n���ԃI�t�Z�b�g��ݒ�
    std::vector<float> startTimeOffsets(boxs.size());
    float offset = 0.0f;
    for (size_t i = 0; i < boxs.size(); ++i) {
        startTimeOffsets[i] = offset;
        // �e�{�b�N�X�̃C�[�W���O�J�n���Ԃ�0.1�b���x�点��
        offset += 0.1f; 
    }

    // �S�Ẵ{�b�N�X�̃C�[�W���O�������s��
    bool allEasingCompleted = true;
    for (size_t i = 0; i < boxs.size(); ++i) {
        float adjustedTime = Time1 - startTimeOffsets[i];

        if (adjustedTime >= 0.0f && adjustedTime <= 1.0f) {
            // ���݂̃{�b�N�X���擾
            BoxObj* currentBox = boxs[i];

            // �C�[�W���O����
            Vector3 startScale(0.0f, 0.0f, 0.0f);
            Vector3 endScale(1.0f, 1.0f, 1.0f);
            currentBox->SetScale(easeInOutElastic(startScale, endScale, adjustedTime));
        }

        if (adjustedTime <= 1.0f) {
            allEasingCompleted = false;
        }
    }

    Time1 += BdeltaTime;

    // �S�Ẵ{�b�N�X�̃C�[�W���O���I���������m�F
    if (allEasingCompleted) {
        Time1 = 0.0f;
        this->SetStartBoxEasing(false);
    }
}

void EasingController::GameEnd(std::vector<Enemy*> enemys, GoalObj* goal)
{
    for (auto enemy : enemys)
    {
        if (enemy->Getgetcaught() && !this->Rookfarst)
        {
            this->Rookfarst = true;
        }
        else if (goal->GetClear())
        {
            this->Goal = true;
        }
    }
}

void EasingController::GoalEasing(DirectX::SimpleMath::Vector3 Plpos, Camera* camera)
{
    //�X�^�[�g�̓J�����̃|�W�V����
    //�S�[���̓v���C���[�̃|�W�V����
    DirectX::SimpleMath::Vector3 EndPos = Plpos;
    DirectX::SimpleMath::Vector3 EndFoucasPos = Plpos;
    EndPos += Vector3(50.0f, 200.0f, 50.0f);


    if (this->EndEasing && this->Goal)
    {
        camera->SetPosition(EaseOutCirc(camera->GetCamPosition(), EndPos, GoalTime));
        camera->SetFoucus(EaseOutCirc(camera->GetCamforcas(), EndFoucasPos, GoalTime));
        GoalTime += deltaTime;
        if (GoalTime >= 1.0f) {
            GoalTime = 0.0f;
            this->EndEasing = false;
            this->Goal = false;
        }
    }


}

bool EasingController::SEasing(Player* Pl, Camera* camera)
{
    //�v���C���[���E
    if (Pl->Getdir().x == 1)
    {
        //����t�����Ƃ��̃J�����̈ʒu�i�C�[�W���O�̃S�[���n�_�j
        DirectX::SimpleMath::Vector3 Plpos = Pl->GetPosition();
        Plpos.y += 140.0f;
        Plpos.x += 100.0f;
        /*Plpos.z += 200.0f;*/
        //����t�����Ƃ��̃J�����̌��Ă���ʒu�i�C�[�W���O�̃S�[���n�_�j
        DirectX::SimpleMath::Vector3 PlFoucusPos;
        PlFoucusPos = Pl->GetPosition();
        PlFoucusPos.y += 80.0f;
        PlFoucusPos.x -= 50.0f;
        if (StikyEasing)
        {
            camera->SetPosition(EaseOutCirc(camera->GetCamPosition(),Plpos, StikyTime));
            camera->SetFoucus(EaseOutCirc(camera->GetCamforcas(),PlFoucusPos, StikyTime));
            StikyTime += deltaTimeStiky;
            if (StikyTime >= 1.0f) {
                StikyTime = 0.0f;
                StikyEasing = false;
                return true;
            }
        }
    }
    //�v���C���[��荶
    else if (Pl->Getdir().x == -1)
    {
        //����t�����Ƃ��̃J�����̈ʒu�i�C�[�W���O�̃S�[���n�_�j
        DirectX::SimpleMath::Vector3 Plpos = Pl->GetPosition();
        Plpos.y += 140.0f;
        Plpos.x -= 100.0f;
        /*Plpos.z += 200.0f;*/
        //����t�����Ƃ��̃J�����̌��Ă���ʒu�i�C�[�W���O�̃S�[���n�_�j
        DirectX::SimpleMath::Vector3 PlFoucusPos;
        PlFoucusPos = Pl->GetPosition();
        PlFoucusPos.y += 80.0f;
        PlFoucusPos.x += 50.0f;
        if (StikyEasing)
        {
            camera->SetPosition(EaseOutCirc(camera->GetCamPosition(), Plpos, StikyTime));
            camera->SetFoucus(EaseOutCirc(camera->GetCamforcas(), PlFoucusPos, StikyTime));
            StikyTime += deltaTimeStiky;
            if (StikyTime >= 1.0f) {
                StikyTime = 0.0f;
                StikyEasing = false;
                return true;
            }
        }
    }
    //�v���C���[��艜
    if (Pl->Getdir().z == 1)
    {
        //����t�����Ƃ��̃J�����̈ʒu�i�C�[�W���O�̃S�[���n�_�j
        DirectX::SimpleMath::Vector3 Plpos = Pl->GetPosition();
        Plpos.y += 140.0f;
        Plpos.z += 100.0f;
        /*Plpos.z += 200.0f;*/
        //����t�����Ƃ��̃J�����̌��Ă���ʒu�i�C�[�W���O�̃S�[���n�_�j
        DirectX::SimpleMath::Vector3 PlFoucusPos;
        PlFoucusPos = Pl->GetPosition();
        PlFoucusPos.y += 80.0f;
        PlFoucusPos.z -= 50.0f;
        if (StikyEasing)
        {
            camera->SetPosition(EaseOutCirc(camera->GetCamPosition(), Plpos, StikyTime));
            camera->SetFoucus(EaseOutCirc(camera->GetCamforcas(), PlFoucusPos, StikyTime));
            StikyTime += deltaTimeStiky;
            if (StikyTime >= 1.0f) {
                StikyTime = 0.0f;
                StikyEasing = false;
                return true;
            }
        }
    }
    //�v���C���[����O
    else if (Pl->Getdir().z == -1)
    {
        //����t�����Ƃ��̃J�����̈ʒu�i�C�[�W���O�̃S�[���n�_�j
        DirectX::SimpleMath::Vector3 Plpos = Pl->GetPosition();
        Plpos.y += 140.0f;
        Plpos.z -= 100.0f;
        /*Plpos.z += 200.0f;*/
        //����t�����Ƃ��̃J�����̌��Ă���ʒu�i�C�[�W���O�̃S�[���n�_�j
        DirectX::SimpleMath::Vector3 PlFoucusPos;
        PlFoucusPos = Pl->GetPosition();
        PlFoucusPos.y += 80.0f;
        PlFoucusPos.z += 50.0f;
        if (StikyEasing)
        {
            camera->SetPosition(EaseOutCirc(camera->GetCamPosition(), Plpos, StikyTime));
            camera->SetFoucus(EaseOutCirc(camera->GetCamforcas(), PlFoucusPos, StikyTime));
            StikyTime += deltaTimeStiky;
            if (StikyTime >= 1.0f) {
                StikyTime = 0.0f;
                StikyEasing = false;
                return true;
            }
        }
    }

    return false;
}

void EasingController::FadeIn(GameUI* FadeUI)
{
    DirectX::SimpleMath::Vector3 FadePos;
    FadePos.x = FadeUI->GetCenter().x;
    FadePos.y = FadeUI->GetCenter().y;

    DirectX::SimpleMath::Vector3 EndPos = Vector3(2880.0f, 0.0f, 540.0f);

    if (Fadein)
    {
        FadeUI->SetFadePos(EaseOutCirc(FadeUI->GetFadePos(), EndPos, Time1));
        Time1 += deltaTime;
        if (Time1 >= 1.0f) {
            Time1 = 0.0f;
            Fadein = false;
        }
    }
}

void EasingController::FadeOut(GameUI* FadeUI)
{
    DirectX::SimpleMath::Vector3 FadePos;
    FadePos.x = FadeUI->GetCenter().x;
    FadePos.y = FadeUI->GetCenter().y;

    DirectX::SimpleMath::Vector3 EndPos = Vector3(960.0f, 0.0f, 540.0f);

    if (Fadeout)
    {
        FadeUI->SetFadePos(EaselnOutBack(FadeUI->GetFadePos(), EndPos, Time1));
        Time1 += deltaTime;
        if (Time1 >= 1.0f) {
            Time1 = 0.0f;
            Fadeout = false;
        }
    }
}

void EasingController::ClearEasing(GameUI* Clear)
{

    if (ClearUIEasingX)
    {
        Clear->SetWH(EaselnSine(Vector3(0.0f, 0.0f, 0.0f), Vector3(2500.0f, 0.0f, 0.0f), Stime));
        Stime += 0.02f;
        if (Stime >= 1.0f)
        {
            Stime = 0.0f;
            ClearUIEasingX = false;
        }
    }
    else if (ClearUIEasingY)
    {
        Clear->SetWH(EaselnSine(Vector3(2500.0f, 0.0f, 0.0f), Vector3(2500.0f, 2500.0f, 0.0f), Stime));
        Stime += 0.02f;
        if (Stime >= 1.0f)
        {
            Stime = 0.0f;
            ClearUIEasingY = false;
        }
    }
}

void EasingController::ImageEasing(GameUI* Image)
{
    if (ImageUIEasing && ImageEasingEnd)
    {
        Image->SetWH(EaselnSine(Vector3(0.0f, 20.0f, 0.0f), Vector3(500.0f, 20.0f, 0.0f), ImageT));
        ImageT += 0.025f;
        if (ImageT >= 1.0f)
        {
            ImageT = 0.0f;
            ImageUIEasing = false;
        }
    }
    else if (!ImageUIEasing && ImageEasingEnd)
    {
        Image->SetWH(EaselnSine(Vector3(500.0f, 20.0f, 0.0f), Vector3(500.0f, 700.0f, 0.0f), ImageT));
        ImageT += 0.025f;
        if (ImageT >= 1.0f)
        {
            ImageT = 0.0f;
            ImageUIEasing = true;
            ImageEasingEnd = false;
        }
    }
}

void EasingController::SelectEasing(GameUI* Select)
{
    if (SelectUIEasing)
    {
        Select->SetWH(EaselnSine(Vector3(300.0f,150.0f,0.0f), Vector3(280.0f,130.0f,0.0f), Stime));
        Stime += 0.03f;
        if (Stime >= 1.0f)
        {
            Stime = 0.0f;
            SelectUIEasing = false;
        }
    }
    else if (!SelectUIEasing)
    {
        Select->SetWH(EaselnSine(Vector3(280.0f, 130.0f, 0.0f), Vector3(300.0f, 150.0f, 0.0f), Stime));
        Stime += 0.03f;
        if (Stime >= 1.0f)
        {
            Stime = 0.0f;
            SelectUIEasing = true;
        }
    }

}





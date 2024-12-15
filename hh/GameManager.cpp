#include "GameManager.h"
#include "Camera.h"
#include "Enemy.h"
#include "easings.h"
#include "Player.h"
#include "GoalObj.h"
#include "BoxObj.h"
#include "CSceneManager.h"
#include "GameResult.h"

using namespace DirectX::SimpleMath;

GameManager::GameManager()
{
    Rookfarst = false;
    Goal = false;
    EndEasing = true;
    Fadein = true;
    Fadeout = true;
}

GameManager::~GameManager()
{

}

bool GameManager::farstEasing(Camera* camera, Player* Pl, GoalObj* goal)
{
    //ゴールのポジション
    DirectX::SimpleMath::Vector3 goalpos = goal->GetPosition();
    goalpos.y += 775.0f;
    goalpos.z += -200.0f;
    //プレイヤーのポジション
    DirectX::SimpleMath::Vector3 plpos = Pl->GetPosition();
    plpos.y += 700.0f;
    plpos.z += -200.0f;
    //目線の座標
    //ゴール
    DirectX::SimpleMath::Vector3 goalFoucusPos;
    goalFoucusPos = goal->GetPosition();
    //プレイヤー
    DirectX::SimpleMath::Vector3 plFoucusPos;
    plFoucusPos = Pl->GetPosition();
    if (startEasing) {
        if (isEasingStart)
        {
            //ポジションのイージング
            camera->SetPosition(EaselnOutBack(goalpos, plpos, Time1));
            //目線のイージング
            camera->SetFoucus(EaselnOutBack(goalFoucusPos, plFoucusPos, Time1));
            Time1 += deltaTime;
            if (Time1 >= 1.0f) {
                Time1 = 0.0f;
                isEasingStart = false;
                return true;
            }
        }
    }
    return false;
}

bool GameManager::EnemyEasing(std::vector<Enemy*> enemys, DirectX::SimpleMath::Vector3 PlPos, Camera* camera, Timer* timer)
{

    if (!enemys.empty() && this->RookEasing == true)
    {
        Enemy* enemy = enemys[0]; // 最初に見つけた敵を使用（複数いる場合の対処は必要に応じて）
        Vector3 enemyPosition = enemy->GetPosition();
        Vector3 enemyPositionFoucus = enemyPosition;
        Vector3 playerPositionFoucus = PlPos;
        Vector3 playerPosition = PlPos;
        enemyPositionFoucus.y += 500.0f;
        enemyPositionFoucus.z += -200.0f;

        enemyPosition.y += 50.0f;
        //敵に見つかった時に見つけた敵に対してカメラのイージング
        if (!timer->IsRunning())
        {
            camera->SetPosition(EaseOutCirc(camera->GetCamPosition(), enemyPositionFoucus, Time1));
            camera->SetFoucus(EaseOutCirc(camera->GetCamforcas(), enemyPosition, Time1));
            Time1 += deltaTime;
            if (Time1 >= 1.0f) {
                Time1 = 0.0f;
                RookEasing = false;
                return true;
            }
        }
//        return false;
    }
    return false;
}

void GameManager::farstBoxEasing(std::vector<BoxObj*> boxs)
{
    // イージングの開始時間オフセットを設定
    std::vector<float> startTimeOffsets(boxs.size());
    float offset = 0.0f;
    for (size_t i = 0; i < boxs.size(); ++i) {
        startTimeOffsets[i] = offset;
        // 各ボックスのイージング開始時間を0.1秒ずつ遅らせる
        offset += 0.1f; 
    }

    // 全てのボックスのイージング処理を行う
    bool allEasingCompleted = true;
    for (size_t i = 0; i < boxs.size(); ++i) {
        float adjustedTime = Time1 - startTimeOffsets[i];

        if (adjustedTime >= 0.0f && adjustedTime <= 1.0f) {
            // 現在のボックスを取得
            BoxObj* currentBox = boxs[i];

            // イージング処理
            Vector3 startScale(0.0f, 0.0f, 0.0f);
            Vector3 endScale(1.0f, 1.0f, 1.0f);
            currentBox->SetScale(easeInOutElastic(startScale, endScale, adjustedTime));
        }

        if (adjustedTime <= 1.0f) {
            allEasingCompleted = false;
        }
    }

    Time1 += BdeltaTime;

    // 全てのボックスのイージングが終了したか確認
    if (allEasingCompleted) {
        Time1 = 0.0f;
        this->SetStartBoxEasing(false);
    }
}

void GameManager::GameEnd(std::vector<Enemy*> enemys, GoalObj* goal)
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

void GameManager::GoalEasing(DirectX::SimpleMath::Vector3 Plpos, Camera* camera)
{
    //スタートはカメラのポジション
    //ゴールはプレイヤーのポジション
    DirectX::SimpleMath::Vector3 EndPos = Plpos;
    DirectX::SimpleMath::Vector3 EndFoucasPos = Plpos;
    EndPos += Vector3(50.0f, 200.0f, 50.0f);


    if (this->EndEasing && this->Goal)
    {
        camera->SetPosition(EaseOutCirc(camera->GetCamPosition(), EndPos, Time1));
        camera->SetFoucus(EaseOutCirc(camera->GetCamforcas(), EndFoucasPos, Time1));
        Time1 += deltaTime;
        if (Time1 >= 1.0f) {
            Time1 = 0.0f;
            this->EndEasing = false;
            this->Goal = false;
        }
    }


}

void GameManager::FadeIn(GameUI* FadeUI)
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

void GameManager::FadeOut(GameUI* FadeUI)
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





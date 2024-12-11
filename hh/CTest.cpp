#include "CTest.h"
#include "GUI.h"
#include "easings.h"



CTest::CTest()
{
    gameTime = new Timer();

    GM = new GameManager();

    CScene::CreateStage(TERRAIN_ID::STAGE_TEST);

    goal = new GoalObj(25.0f, 25.0f, 25.0f);
    goal->SetPosition(this->GetGoalPos());
    goal->CollisionInit(this->GetGoalPos(), Vector3(25.0f, 25.0f, 25.0f));

    //=== Initに使用、MotionName作成 ===
    std::vector<MotionStruct> MS;
    std::vector<MotionStruct> EMS;

    MotionStruct playerMS;
    MotionStruct enemyMS;

    //プレイヤーのモーション
    //Player:Idle
    playerMS.MotionKey = "Idle";
    playerMS.MotionFile = "assets/model/player/playerIdle.fbx";
    MS.push_back(playerMS);
    //Player:Run
    playerMS.MotionKey = "Run";
    playerMS.MotionFile = "assets/model/player/playerRun.fbx";
    MS.push_back(playerMS);
    //Player:Walk
    playerMS.MotionKey = "Walk";
    playerMS.MotionFile = "assets/model/player/playerWalk.fbx";
    MS.push_back(playerMS);
    //Player:Sneakpose
    playerMS.MotionKey = "Spose";
    playerMS.MotionFile = "assets/model/player/sneakpose.fbx";
    MS.push_back(playerMS);
    //Player:SneakWalk
    playerMS.MotionKey = "SWalk";
    playerMS.MotionFile = "assets/model/player/sneakWalk.fbx";
    MS.push_back(playerMS);


    //敵のモーション
    enemyMS.MotionKey = "Idle";
    enemyMS.MotionFile = "assets/model/player/playerIdle.fbx";
    EMS.push_back(enemyMS);

    enemyMS.MotionKey = "Walk";
    enemyMS.MotionFile = "assets/model/player/playerWalk.fbx";
    EMS.push_back(enemyMS);

    enemyMS.MotionKey = "Run";
    enemyMS.MotionFile = "assets/model/player/playerRun.fbx";
    EMS.push_back(enemyMS);


    //プレイヤーの初期化
    Pl = new Player(
        "assets/model/player/Y Bot.fbx",		//モデルファイル
        "assets/model",								//テクスチャファイル
        MS,												//モーションファイル、キー
        "shader/vertexLightingOneSkinVS.hlsl",//VertexShader
        "shader/vertexLightingPS.hlsl"		//PixelShader
    );
    Pl->SetPosition(this->GetPlayerStartPos());
    Pl->SetScale(CharacterScale);
    Pl->CollisionInit(Pl->GetPosition(), Pl->GetCollisionScale());
    Pl->SetMapdata(this->GetMapData());

    EM = new EnemyManager(this->GetMapData(),this->GetWanderingdata());

    //敵の初期化
    for (int a = 0; a < this->GetEnemyStartPoss().size();a++) {
        Enemy* enemy = new Enemy(
            "assets/model/player/X Bot.fbx",
            "assets/model",
            EMS,
            "shader/vertexLightingOneSkinVS.hlsl",
            "shader/vertexLightingPS.hlsl",Pl);
        enemy->SetPosition(this->GetEnemyStartPoss()[a]);  // 敵の位置
        enemy->CollisionInit(enemy->GetPosition(), enemy->GetCollisionScale());
        enemy->SetScale(CharacterScale);
        enemy->Setforward(Vector3(0.0f, 0.0f, -1.0f));
        EM->AddEnemy(enemy);
    }

    EM->SetEnemywandering();

    //レーダーの初期化
    radar = new Radar();
    radar->Init();

    MS.clear();

    EMS.clear();

    field.Init();

    camera = new Camera(this->GetCameraPos());

}

CTest::~CTest()
{

}

void CTest::Update()
{
    if (GM->GetStartBoxEasing())
    {
        GM->farstBoxEasing(BOXS);
        Pl->AnimUpdate();
        EM->EnemysAnimUpdate();
    }
    //最初のカメラのイージング
    else if (!GM->GetStartBoxEasing())
    {
        if (GM->farstEasing(camera, Pl, goal))
        {
            if (gameTime->TameStarflg == true)
            {
                gameTime->Start();
                gameTime->TameStarflg = false;
            }
        }
        else if (gameTime->TameStarflg) {
            //イージング中でもモデルが見えるように
            Pl->AnimUpdate();
            EM->EnemysAnimUpdate();
        }
    }

    //タイマーが走っているなら通常の処理
    if (gameTime->IsRunning())
    {
        Pl->Update();
        //敵全体のアップデート
        EM->UpdateEnemies(Pl, BOXS);
        //敵に見つかったのなら時間を止める
        if (EM->GetRook() && !EM->GetRookNow())
        {
            gameTime->Stop();
        }
        //プレイヤーとすべての敵の位置をレーダーに渡す
        std::vector<DirectX::SimpleMath::Vector3> enemyPositions;
        for (const auto& enemy : EM->GetEnemies()) {
            enemyPositions.push_back(enemy->GetPosition());
        }

        //レーダーのアップデート
        radar->Update(Pl->GetPosition(), enemyPositions);

        //普通のカメラの追尾処理
        if (camera->GetCranning() && !gameTime->TameStarflg)
            camera->LateUpdate(Pl->GetPosition(), camera->GetSpeed());
    }

    //時間が止まっているときの処理
    else if (!gameTime->IsRunning() && gameTime->TameStarflg == false)
    {
        if (GM->EnemyEasing(EM->GetEnemiesWhoSawPlayer(), Pl->GetPosition(), camera, gameTime))
        {
            gameTime->Start();
            EM->SetRookNow(true);
        }
    }

    //ボックスのアップデート
    for (auto& box : BOXS)
    {
        box->Update();
    }

    goal->Update(Pl->square);

    GM->GameEnd(EM->GetEnemies(), goal);


    ////Imguiの処理
    //gui->PlayerUpdate(Pl);
    //gui->CameraUpdate(camera);
    //gui->CollisionUpdate(collision);
    //gui->EnenyUpdate(EM);

}

void CTest::Draw()
{
    //地面描画


    field.Draw();

    //プレイヤーの描画

    Pl->Draw();

    EM->DrawEnemies();

    for (auto& box : BOXS)
    {
        box->Draw();
    }

    goal->Draw();

    radar->Draw(EM->GetEnemies());


    //カメラの描画
    camera->Draw();

}

void CTest::Init()
{

}

//終了処理
void CTest::UnInit()
{
    field.Dispose();

    radar->Dispose();
    delete radar;
    radar = nullptr;

    gameTime->Stop();
    delete gameTime;
    gameTime = nullptr;

    delete EM;
    EM = nullptr;

    delete GM;
    GM = nullptr;

    delete goal;
    goal = nullptr;

    Pl->UnInit();
    delete Pl;
    Pl = nullptr;

    camera->Dispose();
    delete camera;
    camera = nullptr;

    for (auto& box : BOXS)
    {
        delete box;
        box = nullptr;
    }
    BOXS.clear();

}

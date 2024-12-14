#include "STAGE1.h"
#include "GUI.h"
#include "easings.h"
#include "CSceneManager.h"



STAGE1::STAGE1()
{
    gameTime = new Timer();

    GM = new GameManager();

    Dome = new SkyDome();
    Dome->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
    Dome->DrawInit(2000.0f, "assets\\BDome.jpg");

    GoalUI = new GameUI();
    GoalUI->Init("assets\\siro.jpg");
    GoalUI->SetCenter(Vector2(1000.0f, 500.0f));
    GoalUI->SetHeight(2500.0f);
    GoalUI->SetWidth(2500.0f);
    GoalUI->SetColor(Color(0.2, 0.2, 0.2, 0.5f));

    SpaceUI = new GameUI();
    SpaceUI->Init("assets\\SPACEUI.png");
    SpaceUI->SetCenter(Vector2(300.0f, 800.0f));
    SpaceUI->SetHeight(300.0f);
    SpaceUI->SetWidth(500.0f);


    ClearUI = new GameUI();
    ClearUI->Init("assets\\Clear !!.png");
    ClearUI->SetCenter(Vector2(960.0f, 540.0f));
    ClearUI->SetHeight(500.0f);
    ClearUI->SetWidth(900.0f);

    failedUI = new GameUI();
    failedUI->Init("assets\\feiledUI.png");
    failedUI->SetCenter(Vector2(960.0f, 540.0f));
    failedUI->SetHeight(500.0f);
    failedUI->SetWidth(900.0f);


    CScene::CreateStage(TERRAIN_ID::STAGE_1);

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
    //PlayerGoal
    playerMS.MotionKey = "Goal";
    playerMS.MotionFile = "assets/model/player/PlayerGoalIdle.fbx";
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

    EM = new EnemyManager(this->GetMapData(), this->GetWanderingdata());

    //敵の初期化
    for (int a = 0; a < this->GetEnemyStartPoss().size(); a++) {
        Enemy* enemy = new Enemy(
            "assets/model/player/X Bot.fbx",
            "assets/model",
            EMS,
            "shader/vertexLightingOneSkinVS.hlsl",
            "shader/vertexLightingPS.hlsl", Pl);
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


    camera = new Camera(this->GetCameraPos());

}

STAGE1::~STAGE1()
{

}

void STAGE1::Update()
{
    //ゲーム開始の処理
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
        if (camera->GetCranning() && !gameTime->TameStarflg && GM->GetEndEasing())
            camera->LateUpdate(Pl->GetPosition(), camera->GetSpeed());
    }

    //時間が止まっているときの処理
    else if (!gameTime->IsRunning() && gameTime->TameStarflg == false)
    {
        //プレイヤーを見つけた敵に対してイージング
        if (GM->EnemyEasing(EM->GetEnemiesWhoSawPlayer(), Pl->GetPosition(), camera, gameTime))
        {
            //gameTime->Start();
            EM->SetRookNow(true);
        }
    }

    //ボックスのアップデート
    for (auto& box : BOXS)
    {
        box->Update();
    }

    //ドームのアップデート
    Dome->Update();

    //ゴールのアップデート
    goal->Update(Pl->square);

    //ゴールにぶつかったか？
    GM->GameEnd(EM->GetEnemies(), goal);

    //ゴールにぶつかったらイージング
    if (GM->GetGoal() && GM->GetEndEasing())
    {   
        GM->GoalEasing(Pl->GetPosition(), camera);
    }
    //イージングが終わったら
    else if (!GM->GetEndEasing())
    {
        //ゴールした時のモーションにする
        Pl->SetGoalState();
        //アニメーションの再生
        Pl->AnimUpdate();
        //時間を止める
        gameTime->Stop();

        if (Input::Get()->GetKeyTrigger(DIK_SPACE))
        {
            CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESALT);
        }
    }
    else if (EM->GetRookNow())
    {
        if (Input::Get()->GetKeyTrigger(DIK_SPACE))
        {
            CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESALT);
        }
    }




    //Imguiの処理
 /*   gui->PlayerUpdate(Pl);
    gui->CameraUpdate(camera);
    gui->CollisionUpdate(collision);
    gui->EnenyUpdate(EM);*/

}

void STAGE1::Draw()
{

    EM->DrawEnemies();

    //プレイヤーの描画

    Pl->Draw();

    for (auto& box : BOXS)
    {
        box->Draw();
    }

    Dome->Draw();

    goal->Draw();

    if (!GM->GetEndEasing())
    {
        GoalUI->Draw();
        SpaceUI->Draw();
        ClearUI->Draw();
    }
    else if (EM->GetRookNow())
    {
        GoalUI->Draw();
        SpaceUI->Draw();
        failedUI->Draw();
    }
    else
    {
        radar->Draw(EM->GetEnemies());
    }
    //カメラの描画
    camera->Draw();
}

void STAGE1::Init()
{

}

void STAGE1::UnInit()
{

    radar->Dispose();
    delete radar;
    radar = nullptr;

    gameTime->Stop();
    delete gameTime;
    gameTime = nullptr;

    delete EM;
    EM = nullptr;

    delete Dome;
    Dome = nullptr;

    delete GM;
    GM = nullptr;

    delete SpaceUI;
    SpaceUI = nullptr;

    delete goal;
    goal = nullptr;

    delete GoalUI;
    GoalUI = nullptr;

    delete ClearUI;
    ClearUI = nullptr;

    delete failedUI;
    failedUI = nullptr;

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

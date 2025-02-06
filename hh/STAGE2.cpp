#include "STAGE2.h"
#include "GUI.h"
#include "easings.h"
#include "CSceneManager.h"



STAGE2::STAGE2()
{
    gameTime = new Timer(true);

    UM = new UIManager();

    uragiri = new Shadow();
    uragiri->Init();

    GM = new EasingController();

    Dome = new SkyDome();
    Dome->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
    Dome->DrawInit(1850.0f, "assets\\Texture\\DomeS.jpeg");


    //UIの初期化
    GoalUI = new GameUI();
    GoalUI->Init("assets\\Texture\\siro.jpg");
    GoalUI->SetCenter(Vector2(1000.0f, 500.0f));
    GoalUI->SetHeight(0.0f);
    GoalUI->SetWidth(0.0f);
    GoalUI->SetColor(Color(0.2f, 0.2f, 0.2f, 0.8f));
    UM->AddUI("GoalUI", GoalUI);

    ClearUI = new GameUI();
    ClearUI->Init("assets\\Texture\\Clear !!.png");
    ClearUI->SetCenter(Vector2(960.0f, 540.0f));
    ClearUI->SetHeight(500.0f);
    ClearUI->SetWidth(900.0f);
    UM->AddUI("ClearUI", ClearUI);

    failedUI = new GameUI();
    failedUI->Init("assets\\Texture\\feiledUI.png");
    failedUI->SetCenter(Vector2(960.0f, 540.0f));
    failedUI->SetHeight(500.0f);
    failedUI->SetWidth(900.0f);
    UM->AddUI("failedUI", failedUI);

    Fade = new GameUI();
    Fade->Init("assets\\Texture\\siro.jpg");
    Fade->SetCenter(Vector2(960.0f, 540.0f));
    Fade->SetHeight(1080.0f);
    Fade->SetWidth(1920.0f);
    Fade->SetColor(Color(0.0f, 0.0f, 0.0f, 1.0f));

    StartUI = new GameUI();
    StartUI->Init("assets\\Texture\\siro.jpg");
    StartUI->SetCenter(Vector2(960.0f, 540.0f));
    StartUI->SetHeight(300.0f);
    StartUI->SetWidth(500.0f);
    StartUI->SetColor(Color(0.0f, 0.5f, 0.5f, 0.5f));
    UM->AddUI("StartUI", StartUI);

    explainUI = new GameUI();
    explainUI->Init("assets\\Texture\\setumei.png");
    explainUI->SetCenter(Vector2(960.0f, 540.0f));
    explainUI->SetHeight(300.0f);
    explainUI->SetWidth(500.0f);
    explainUI->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
    UM->AddUI("explainUI", explainUI);

    PushUI = new GameUI();
    PushUI->Init("assets\\Texture\\PushSpace.png");
    PushUI->SetCenter(Vector2(1500.0f, 850.0f));
    PushUI->SetHeight(200.0f);
    PushUI->SetWidth(600.0f);
    UM->AddUI("pushspace", PushUI);


    CScene::CreateStage(TERRAIN_ID::STAGE_2);

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

    EM = new EnemyManager(this->GetMapData(), this->GetWanderingdata(), this->GetEparameterdata());

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
    EM->SetEnemyParameter();

    UM->InitEnemyUI(EM->GetEnemies());
    UM->InitPlayerUI();
    UM->InitTimeUI();

    //レーダーの初期化
    radar = new Radar();
    radar->Init();

    MS.clear();

    EMS.clear();

    camera = new Camera(this->GetCameraPos());

    Scamera = new Camera(Vector3(Pl->GetPosition().x, Pl->GetPosition().y + 800.0f, Pl->GetPosition().z));
    Scamera->SetFoucus(Pl->GetPosition());
}

STAGE2::~STAGE2()
{

}

void STAGE2::Update()
{

    GM->FadeIn(Fade);


    //ゲーム開始の処理
    if (GM->GetStartBoxEasing() && !GM->GetFadein())
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

        }
        else if (gameTime->TameStarflg && GM->GetisEasingstart()) {
            //イージング中でもモデルが見えるように
            Pl->AnimUpdate();
            EM->EnemysAnimUpdate();
        }
        else if (!GM->GetisEasingstart())
        {
            if (Input::Get()->GetKeyTrigger(DIK_SPACE) && !EM->GetRookNow() && !GM->GetGoal())
            {
                gameTime->StartCountDown(120);
                gameTime->TameStarflg = false;
            }
        }
    }




    //タイマーが走っているなら通常の処理
    if (gameTime->IsRunning())
    {

        //プレイヤーのアップデート
        Pl->Update();

        //エネミーのアップデート
        EM->UpdateEnemies(Pl, BOXS);

        //敵に見つかったのなら時間を止める
        if (EM->GetRook() && !EM->GetRookNow())
        {
            gameTime->Stop();
        }

        //レーダーのアップデート
        radar->Update(Pl->GetPosition(), EM->GetEnemies());

        //普通のカメラの追尾処理
        if (camera->GetCranning() && !gameTime->TameStarflg && GM->GetEndEasing() && !Pl->GetSticky())
            camera->LateUpdate(Pl->GetPosition(), camera->GetSpeed(), 500.0f, Pl->GetFPSeye(), Pl->GetFacingDirection());
        else if (Pl->GetSticky())
        {
            if (GM->SEasing(Pl, camera))
            {
                GM->SetStikyEasing(true);
            }
        }
        Scamera->SetPosition(Vector3(Pl->GetPosition().x, Pl->GetPosition().y + 800, Pl->GetPosition().z));
        Scamera->SetFoucus(Pl->GetPosition());
    }

    //時間が止まっているときの処理
    else if (!gameTime->IsRunning() && gameTime->TameStarflg == false)
    {
        //プレイヤーを見つけた敵に対してイージング
        if (GM->EnemyEasing(EM->GetEnemiesWhoSawPlayer(), Pl->GetPosition(), camera, gameTime))
        {
            XA_Stop(SOUND_LABEL_BGM);
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
        XA_Stop(SOUND_LABEL_BGM);
        GM->GoalEasing(Pl->GetPosition(), camera);
    }

    //ゴールした時の処理
    else if (!GM->GetEndEasing())
    {
        //ゴールした時のモーションにする
        Pl->SetGoalState();
        //アニメーションの再生
        Pl->AnimUpdate();
        //時間を止める
        gameTime->Stop();

        if (GM->GetClearUIEasingX() || GM->GetClearUIEasingY())
        {
            GM->ClearEasing(GoalUI);
        }

        if (Input::Get()->GetKeyTrigger(DIK_SPACE) && !GM->GetClearUIEasingY())
        {
            XA_Play(SOUND_LABEL_KETEI);
            this->FadeOut = true;
        }
        else if (this->FadeOut)
        {
            GM->FadeOut(Fade);
            if (!GM->GetFadeout())
            {
                CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESALT);
            }
        }
    }
    //敵に見つかった時の処理
    else if (EM->GetRookNow())
    {
        if (Input::Get()->GetKeyTrigger(DIK_SPACE))
        {
            XA_Play(SOUND_LABEL_KETEI);
            this->FadeOut = true;
        }
        else if (this->FadeOut)
        {
            GM->FadeOut(Fade);
            if (!GM->GetFadeout())
            {
                CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESALT);
            }
        }
    }
    else if (gameTime->IsTimeUp() && !gameTime->TameStarflg)
    {
        gameTime->Stop();
        gameTime->SetTimeUp(true);
        if (Input::Get()->GetKeyTrigger(DIK_SPACE))
        {
            XA_Play(SOUND_LABEL_KETEI);
            this->FadeOut = true;
        }
        else if (this->FadeOut)
        {
            GM->FadeOut(Fade);
            if (!GM->GetFadeout())
            {
                CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESALT);
            }
        }

    }


    //Imguiの処理
    //gui->PlayerUpdate(Pl);
    //gui->CameraUpdate(camera);
    //gui->EnenyUpdate(EM);


}

void STAGE2::Draw()
{
    camera->Draw();

    Dome->Draw();

    if (!GM->GetFadein())
    {
        uragiri->Begin();

        Scamera->LightDraw();

        Pl->ShadowDraw();

        EM->ShadowDraw();

        uragiri->End();

        camera->Draw();



        for (auto& box : BOXS)
        {
            box->Draw();
        }

        EM->DrawEnemies();

        Pl->Draw();

        goal->Draw();

    }

    if (!GM->GetEndEasing())
    {
        UM->ListCler();
        UM->SetActiveUI({ "GoalUI" });
        if (!GM->GetClearUIEasingY())
        {
            UM->SetActiveUI({ "GoalUI","ClearUI","pushspace" });
        }
    }
    else if (EM->GetRookNow() || gameTime->GetTimeUp())
    {
        UM->ListCler();
        GoalUI->SetHeight(2500.0f);
        GoalUI->SetWidth(2500.0f);
        UM->SetActiveUI({ "GoalUI","failedUI","pushspace" });
    }
    else if (!GM->GetisEasingstart())
    {
        UM->ListCler();
        UM->PlayerStateUI(Pl);
        UM->EnemyUIActive(EM->GetEnemies());
        UM->TimeactiveUI(gameTime);
        radar->Draw(EM->GetEnemies());
    }

    if (gameTime->TameStarflg == true && !GM->GetisEasingstart())
    {
        UM->ListCler();
        UM->SetActiveUI({ "StartUI" });
        UM->SetActiveUI({ "explainUI" });
    }
    UM->Draw();

    Fade->Draw();

}

void STAGE2::Init()
{

}

void STAGE2::UnInit()
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

    delete goal;
    goal = nullptr;

    delete UM;
    UM = nullptr;

    delete Fade;
    Fade = nullptr;

    delete uragiri;
    uragiri = nullptr;

    delete Scamera;
    Scamera = nullptr;


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

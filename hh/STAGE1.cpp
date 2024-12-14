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

    //=== Init�Ɏg�p�AMotionName�쐬 ===
    std::vector<MotionStruct> MS;
    std::vector<MotionStruct> EMS;

    MotionStruct playerMS;
    MotionStruct enemyMS;

    //�v���C���[�̃��[�V����
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


    //�G�̃��[�V����
    enemyMS.MotionKey = "Idle";
    enemyMS.MotionFile = "assets/model/player/playerIdle.fbx";
    EMS.push_back(enemyMS);

    enemyMS.MotionKey = "Walk";
    enemyMS.MotionFile = "assets/model/player/playerWalk.fbx";
    EMS.push_back(enemyMS);

    enemyMS.MotionKey = "Run";
    enemyMS.MotionFile = "assets/model/player/playerRun.fbx";
    EMS.push_back(enemyMS);


    //�v���C���[�̏�����
    Pl = new Player(
        "assets/model/player/Y Bot.fbx",		//���f���t�@�C��
        "assets/model",								//�e�N�X�`���t�@�C��
        MS,												//���[�V�����t�@�C���A�L�[
        "shader/vertexLightingOneSkinVS.hlsl",//VertexShader
        "shader/vertexLightingPS.hlsl"		//PixelShader
    );
    Pl->SetPosition(this->GetPlayerStartPos());
    Pl->SetScale(CharacterScale);
    Pl->CollisionInit(Pl->GetPosition(), Pl->GetCollisionScale());
    Pl->SetMapdata(this->GetMapData());

    EM = new EnemyManager(this->GetMapData(), this->GetWanderingdata());

    //�G�̏�����
    for (int a = 0; a < this->GetEnemyStartPoss().size(); a++) {
        Enemy* enemy = new Enemy(
            "assets/model/player/X Bot.fbx",
            "assets/model",
            EMS,
            "shader/vertexLightingOneSkinVS.hlsl",
            "shader/vertexLightingPS.hlsl", Pl);
        enemy->SetPosition(this->GetEnemyStartPoss()[a]);  // �G�̈ʒu
        enemy->CollisionInit(enemy->GetPosition(), enemy->GetCollisionScale());
        enemy->SetScale(CharacterScale);
        enemy->Setforward(Vector3(0.0f, 0.0f, -1.0f));
        EM->AddEnemy(enemy);
    }

    EM->SetEnemywandering();

    //���[�_�[�̏�����
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
    //�Q�[���J�n�̏���
    if (GM->GetStartBoxEasing())
    {
        GM->farstBoxEasing(BOXS);
        Pl->AnimUpdate();
        EM->EnemysAnimUpdate();
    }
    //�ŏ��̃J�����̃C�[�W���O
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
            //�C�[�W���O���ł����f����������悤��
            Pl->AnimUpdate();
            EM->EnemysAnimUpdate();
        }
    }




    //�^�C�}�[�������Ă���Ȃ�ʏ�̏���
    if (gameTime->IsRunning())
    {
        Pl->Update();
        //�G�S�̂̃A�b�v�f�[�g
         EM->UpdateEnemies(Pl, BOXS);
        //�G�Ɍ��������̂Ȃ玞�Ԃ��~�߂�
        if (EM->GetRook() && !EM->GetRookNow())
        {
            gameTime->Stop();
        }
        //�v���C���[�Ƃ��ׂĂ̓G�̈ʒu�����[�_�[�ɓn��
        std::vector<DirectX::SimpleMath::Vector3> enemyPositions;
        for (const auto& enemy : EM->GetEnemies()) {
            enemyPositions.push_back(enemy->GetPosition());
        }

        //���[�_�[�̃A�b�v�f�[�g
        radar->Update(Pl->GetPosition(), enemyPositions);

        //���ʂ̃J�����̒ǔ�����
        if (camera->GetCranning() && !gameTime->TameStarflg && GM->GetEndEasing())
            camera->LateUpdate(Pl->GetPosition(), camera->GetSpeed());
    }

    //���Ԃ��~�܂��Ă���Ƃ��̏���
    else if (!gameTime->IsRunning() && gameTime->TameStarflg == false)
    {
        //�v���C���[���������G�ɑ΂��ăC�[�W���O
        if (GM->EnemyEasing(EM->GetEnemiesWhoSawPlayer(), Pl->GetPosition(), camera, gameTime))
        {
            //gameTime->Start();
            EM->SetRookNow(true);
        }
    }

    //�{�b�N�X�̃A�b�v�f�[�g
    for (auto& box : BOXS)
    {
        box->Update();
    }

    //�h�[���̃A�b�v�f�[�g
    Dome->Update();

    //�S�[���̃A�b�v�f�[�g
    goal->Update(Pl->square);

    //�S�[���ɂԂ��������H
    GM->GameEnd(EM->GetEnemies(), goal);

    //�S�[���ɂԂ�������C�[�W���O
    if (GM->GetGoal() && GM->GetEndEasing())
    {   
        GM->GoalEasing(Pl->GetPosition(), camera);
    }
    //�C�[�W���O���I�������
    else if (!GM->GetEndEasing())
    {
        //�S�[���������̃��[�V�����ɂ���
        Pl->SetGoalState();
        //�A�j���[�V�����̍Đ�
        Pl->AnimUpdate();
        //���Ԃ��~�߂�
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




    //Imgui�̏���
 /*   gui->PlayerUpdate(Pl);
    gui->CameraUpdate(camera);
    gui->CollisionUpdate(collision);
    gui->EnenyUpdate(EM);*/

}

void STAGE1::Draw()
{

    EM->DrawEnemies();

    //�v���C���[�̕`��

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
    //�J�����̕`��
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

#include	<SimpleMath.h>
#include	<memory>
#include	"CShader.h"
#include	"CAnimationData.h"
#include	"CAnimationMesh.h"
#include	"AnimObj.h"
#include	"Input.h"
#include	"AnimScene.h"


AnimScene::AnimScene()
{

}

AnimScene::~AnimScene()
{

}

void AnimScene::Update()
{
    Pl->Update();

    //for (auto& enemy : ENEMYS) {
    //    if (enemy->IsInView(enemy->GetPosition(), enemy->PositionForward(), enemy->GetFov(), Pl->GetPosition(), enemy->Getlength())) {
    //        // �Ή�����R�[�h
    //    }
    //    enemy->Update();
    //}

    ////�v���C���[�Ƃ��ׂĂ̓G�̈ʒu�����[�_�[�ɓn��
    //std::vector<DirectX::SimpleMath::Vector3> enemyPositions;
    //for (const auto& enemy : ENEMYS) {
    //    enemyPositions.push_back(enemy->GetPosition());
    //}

    //radar->Update(Pl->GetPosition(), enemyPositions);

    //box->Update();

    //camera->LateUpdate(Pl->GetPosition(), camera->GetSpeed());
}

void AnimScene::Draw()
{
 //   Pl->Draw();

 //   for (auto& enemy : ENEMYS) {
 //       enemy->EnemyDraw();
 //   }

 //   box->Draw();

 //   radar->Draw(ENEMYS);

	//camera->Draw();
}

void AnimScene::Init()
{
	//camera = new Camera();
	//camera->Init();

 //   radar = new Radar();
 //   radar->Init();

 //   //=== Init�Ɏg�p�AMotionName�쐬 ===
 //   std::vector<MotionStruct> MS;

 //   MotionStruct playerMS;

 //   //=== Player:Idle ===
 //   playerMS.MotionKey = "Idle";
 //   playerMS.MotionFile = "assets/model/player/playerIdle.fbx";
 //   MS.push_back(playerMS);
 //   //=== Player:Walk ===
 //   playerMS.MotionKey = "Walk";
 //   playerMS.MotionFile = "assets/model/player/playerWalk.fbx";
 //   MS.push_back(playerMS);
 //   //=== Player:Run ===
 //   playerMS.MotionKey = "Run";
 //   playerMS.MotionFile = "assets/model/player/playerRun.fbx";
 //   MS.push_back(playerMS);

 //   Pl = new Player("assets/model/player/playerModel.fbx",		//���f���t�@�C��
 //       "assets/model",								//�e�N�X�`���t�@�C��
 //       MS,												//���[�V�����t�@�C���A�L�[
 //       "shader/vertexLightingOneSkinVS.hlsl",//VertexShader
 //       "shader/vertexLightingPS.hlsl"		//PixelShader
 //   );
 //   for (int i = 0; i < enemyCount; ++i) {
 //       Enemy* enemy = new Enemy(
 //           "assets/model/player/playerModel.fbx",
 //           "assets/model",
 //           MS,
 //           "shader/vertexLightingOneSkinVS.hlsl",
 //           "shader/vertexLightingPS.hlsl",Pl);
 //       enemy->DrawInit();
 //       enemy->SetPosition(Vector3(150.0f * i, 0.0f, 0.0f));  // �G�̈ʒu�𒲐�
 //       enemy->SetScale(CharacterScale);
 //       ENEMYS.push_back(enemy);
 //   }


 //   MS.clear();

 //   box = new BoxMesh();


}

void AnimScene::UnInit()
{
 //   Pl->UnInit();
 //   delete Pl;

 //   radar->Dispose();
 //   delete radar;

 //   for (auto& enemy : ENEMYS) {
 //       delete enemy;
 //   }
 //   ENEMYS.clear();

	//delete camera;

 //   delete box;
}

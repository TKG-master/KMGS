#include "Enemy.h"
#include "CBoxMesh.h"
#include "Player.h"
#include "CScene.h"
#include "BoxObj.h"
#include "GameResult.h"
#include "Camera.h"
#include "easings.h"
#include <algorithm>
#include <iostream>

using namespace DirectX::SimpleMath;



void Enemy::Init(std::string ModelName, std::string TexFolderPath, std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader)
{
    //モデル読み込み等
    Character::Init(ModelName, TexFolderPath, MotionName, vShader, pShader);
    this->DrawInit();
    STATUS = IDLE;
    this->square.type = ObjectType::ENEMY;
}

void Enemy::UIInit(int nam)
{
    float shift = 150.0f;

    shift *= nam;

    UI = new GameUI();
    UI->Init("assets\\Texture\\EnemyUI.png");
    UI->SetHeight(100.0f);
    UI->SetWidth(100.0f);
    UI->SetCenter(Vector2(1800.0f - shift, 900.0f));

    suspiciousUI = new GameUI();
    suspiciousUI->Init("assets\\Texture\\hatenaUI.png");
    suspiciousUI->SetHeight(100.0f);
    suspiciousUI->SetWidth(100.0f);
    suspiciousUI->SetCenter(Vector2(1800.0f - shift, 800.0f));
}

Enemy::Enemy(std::string ModelName, std::string TexFolderPath, std::vector<MotionStruct> MotionName, std::string vShader, std::string pShader, const Player* Pl)
{
    //モデル読み込み等
    Character::Init(ModelName, TexFolderPath, MotionName, vShader, pShader);
    this->DrawInit();
    STATUS = IDLE;
    this->playerdate = Pl;
    this->square.type = ObjectType::ENEMY;
    time = new Timer(true);


    AI = new EnemyAI();
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

    delete UI;
    UI = nullptr;

    delete suspiciousUI;
    suspiciousUI = nullptr;

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


    // テクスチャの読み込み
    bool sts = e_Texture.Load("assets\\Texture\\siro.jpg");
    assert(sts == true);
}

void Enemy::Update()
{
    // アニメーションのアップデート
    AnimUpdate();

    //敵の動きのアップデート
    MoveUpdate();


    //当たり判定の押し出し処理
    for (auto it = CScene::BOXS.begin(); it != CScene::BOXS.end(); it++)
    {
        BoxObj* box = *it;
        //当たり判定---------------------------------//
        if (box->square.type == ObjectType::BOX)
        {
            if (CCollision::Square3DCollision(this->square, box->square))
            {
                //当たり判定の補完
                CCollision::ResolveCollision(this->square, box->square);
                this->squareUpdate();
            }
        }
    }

    //進行方向に基づいて回転させる
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

DirectX::SimpleMath::Vector3 Enemy::PositionForward()
{
    this->SaveForward.x = this->GetPosition().x + (this->Getforward().x * 0.0001f);
    this->SaveForward.z = this->GetPosition().z + (this->Getforward().z * 0.0001f);

    return this->SaveForward;
}

//敵の見えている範囲の描画
void Enemy::viewDraw()
{
    ID3D11DeviceContext* deviceContext = Renderer::GetDeviceContext();

    // トポロジーをセット（旧プリミティブタイプ）
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 中心点の設定
    //扇形の原点を敵のポジションに指定
    fanVertices[0].Position = this->GetPosition() + (this->GetPosition() * -1);
    //扇形になんの色を付けるかの指定
    DirectX::SimpleMath::Color fanColor(color);
    fanVertices[0].Diffuse = fanColor;


    //扇形の各セグメントの位置を計算
    for (int i = 0; i <= numSegments; ++i)
    {

        float angle = -viewAngle / 2 + viewAngle * i / numSegments;

        //１セグメントの点のｘ軸とｚ軸の計算
        float x = cos(angle) * viewDistance * this->Getview();
        float z = sin(angle) * viewDistance * viewZ;

        //扇形が埋もれないようにy軸に+0.1f
        point = DirectX::SimpleMath::Vector3(x, 0.1f, z);

        // エネミーの向きに応じて回転
        rotation = DirectX::SimpleMath::Matrix::CreateRotationY(atan2(90.0f, 0.0f));
        point = DirectX::SimpleMath::Vector3::Transform(point, rotation);

        // エネミーの位置を基準に移動
        point += this->GetPosition() + (this->GetPosition() * -1);

        //０は原点だからiにプラス１
        fanVertices[i + 1].Position = point;
        fanVertices[i + 1].Diffuse = fanColor;

    }

    //インデックスに登録
    std::vector<unsigned int> fanIndices;
    for (int i = 1; i < numSegments + 1; ++i)
    {
        fanIndices.push_back(0);
        fanIndices.push_back(i + 1);
        fanIndices.push_back(i);
    }

    if (this->Search)
    {
        this->SetColor(Color(1.0f, 0.0f, 0.0f, 0.8f));
    }
    else if (!this->Search)
    {
        this->SetColor(Color(1.0f, 1.0f, 0.0f, 0.8f));
    }

    // 頂点バッファを作成して設定
    e_VertexBuffer.Create(fanVertices);
    e_VertexBuffer.SetGPU();

    // インデックスバッファを作成して設定
    e_IndexBuffer.Create(fanIndices);
    e_IndexBuffer.SetGPU();

    //シェーダーの設定
    e_Shader.SetGPU();

    e_Material.SetGPU();
    //テクスチャの設定
    e_Texture.SetGPU();

    // トポロジーを三角形リストに設定して描画
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext->DrawIndexed(fanIndices.size(), 0, 0);

}
//敵のUIの描画
void Enemy::UIDraw()
{
    if (this->GetSearch())
    {
        suspiciousUI->Draw();
    }
    UI->Draw();
}
//敵の視野範囲にプレイヤーが入ってるかの判定
bool Enemy::IsInView(DirectX::SimpleMath::Vector3 eyepos, DirectX::SimpleMath::Vector3 lookat, float fov, DirectX::SimpleMath::Vector3 checkpoint, float length)
{
    //向きがすべて０の時にどこも向いてない判定
    if (lookat.x == 0 && lookat.z == 0 && lookat.y == 0)
    {
        return false;
    }
    // チェック対象と視点を結ぶベクトルを計算
    DirectX::SimpleMath::Vector3 vecobj;
    vecobj = checkpoint - eyepos;
    // オブジェクトとの距離を求める
    float objlength = vecobj.Length();
    // 距離範囲外ならfalse
    if (objlength > length) {
        test = false;
        return false;
    }
    // 視線ベクトル
    DirectX::SimpleMath::Vector3 vecview;
    vecview = lookat - eyepos;
    // 正規化
    vecview.Normalize();
    vecobj.Normalize();
    // 内積を計算
    float dotobj = vecview.Dot(vecobj);
    //// 回転
    DirectX::SimpleMath::Matrix mtx;

    mtx = mtx.CreateRotationX(fov / 2.0f) * mtx.CreateRotationZ(fov / 2.0f) * mtx.CreateRotationY(fov / 2.0f);

    DirectX::SimpleMath::Vector3 vecrotview;
    vecrotview = vecview.Transform(vecview, mtx);
    // 内積を計算
    float dotrotview = vecview.Dot(vecrotview);
    // 視野角範囲内？
    if (dotrotview <= dotobj) {
        //if (RayLookHit())
        //{
            return true;
        //}
//        false;
    }
    else {
        return false;
    }

}
//敵の向いている向きとモデルの向きを合わせる
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
//敵がプレイヤーを見つけていない時の動き
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

    //徘徊モード
    if (!this->GetSearch() && !this->back)
    {
        this->Wanderaround();
    }
    //探しに行っている
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
        // タイマーがまだ開始されていない場合に開始する
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
    currentPathIndex = 1;  // 経路の最初の地点から開始
}

void Enemy::SetwanderingPath(const std::vector<DirectX::SimpleMath::Vector3>& wanderingPath)
{
    wandering_path = wanderingPath;
    currentwanderingpathIndex = 1;
}

void Enemy::Wanderaround()
{

    // 次の位置
    targetPos = wandering_path[currentwanderingpathIndex];

    // 現在の位置
    currentPosition = this->GetPosition();

    // 移動量を計算
    direction = targetPos - currentPosition;
    float distance = direction.Length();

    // 次の位置に到達した場合の判定を緩める
    float tolerance = MoveSpeed * 2.5f;
    if (distance < tolerance) {
        // 次の位置に到達した場合
        this->SetPosition(targetPos);
        currentwanderingpathIndex++;
        this->SetState(EStateType::Lookaround);
    }
    else {
        // 移動量を正規化して速度を掛ける
        direction.Normalize();
        this->SetPosition(currentPosition + direction * MoveSpeed);
    }

     //進行方向に向けて回転を更新（イージングを使用）
    if (direction.LengthSquared() > 0.0f) {
        DirectX::SimpleMath::Vector3 currentForward = this->Getforward();
        DirectX::SimpleMath::Vector3 newForward = EaseInCirc(currentForward, direction, Time1);
        this->Setforward(newForward);
        Time1 += deltaTime;
        if (Time1 >= 1.0f) {
            Time1 = 0.5f;
        }
    }
}

void Enemy::FollowPath()
{
    // 経路がないか、すでに経路の終点に到達している場合
    if (path.empty() || currentPathIndex >= path.size()) {
        //探索モードが終わったら
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
            this->bookRead = true;
          return;
        }
        //徘徊ルートに戻ったら
        else if(this->back)
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

    // 次の位置
    DirectX::SimpleMath::Vector3 targetPos = path[currentPathIndex];

    // 現在の位置
    DirectX::SimpleMath::Vector3 currentPosition = this->GetPosition();

    // 移動量を計算
    DirectX::SimpleMath::Vector3 direction = targetPos - currentPosition;
    float distance = direction.Length();

    // 次の位置に到達した場合の判定を緩める
    float tolerance = MoveSpeed * 2.5f;
    if (distance < tolerance) {
        // 次の位置に到達した場合
        this->SetPosition(targetPos);
        currentPathIndex++;
    }
    else {
        // 移動量を正規化して速度を掛ける
        direction.Normalize();
        this->SetPosition(currentPosition + direction * MoveSpeed * 1.5f);
    }

    // 進行方向に向けて回転を更新
    if (direction.LengthSquared() > 0.0f) {
        //向きをセット
        this->Setforward(direction);
        UpdateRotation();  // 回転の更新
    }

}

bool Enemy::RayLookHit()
{
    // プレイヤーに向かってレイを飛ばす
    rayDirection = playerdate->GetPosition() - this->GetPosition();
    Vector3 Epos = this->GetPosition();
    // レイの発射位置をY軸方向に少し高くする
    Epos.y += rayY;
    //正規化
    rayDirection.Normalize();
    if (CCollision::RayIntersectsBox(Epos, rayDirection, playerdate->square,CScene::BOXS, hitDis)) {
        this->SetSearch(true);
        return true;
    }
    return false;
}

bool Enemy::RayLookBook(DirectX::SimpleMath::Vector3 pos,SQUARE3D square)
{
    // プレイヤーに向かってレイを飛ばす
    rayDirection = pos - this->GetPosition();
    Vector3 Epos = this->GetPosition();
    // レイの発射位置をY軸方向に少し高くする
    Epos.y += rayY;
    //正規化
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

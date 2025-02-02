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
    //モデル読み込み等
    Character::Init(ModelName, TexFolderPath, MotionName, vShader, pShader);
    this->DrawInit();
    STATUS = IDLE;
    this->square.type = ObjectType::ENEMY;
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

//敵の見えている範囲の描画
void Enemy::viewDraw()
{
    if (!this->GetbookRead())
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

        if (this->GetState() == EStateType::Serch)
        {
            this->SetColor(Color(1.0f, 0.0f, 0.0f, 0.8f));
        }
        else
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
        //this->test = false;
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
            return true;
    }
    else {
        return false;
    }

}
//境界円の判定
bool Enemy::InInViewCircle(DirectX::SimpleMath::Vector3 eyepos, DirectX::SimpleMath::Vector3 lookat, float fov, DirectX::SimpleMath::Vector3 circlecenter, float radius, float length)
{
    // 向きがすべて0のときはどこも向いていないとみなす
    if (lookat.x == 0 && lookat.z == 0 && lookat.y == 0) {
        return false;
    }

    bool sts = true;


    // チェック対象と視点を結ぶベクトル
    Vector3 vecobj;
    vecobj = circlecenter - eyepos;
    // オブジェクトとの距離を求める
    float objlength = vecobj.Length();
    // 距離範囲外？
    if (objlength - radius > length) {
        return false;
    }
    // 視野の上限ベクトルを求める
    // 回転
    Matrix mtx;
    mtx = mtx.CreateRotationY(fov / 2.0f);// 視野角の半分を指定して行列を作成
    Vector3 lookatplus;
    Vector3 lookatminus;

    // 視線ベクトル
    Vector3 v;
    v = lookat - eyepos;
    lookatplus = v.Transform(v, mtx);// 視線ベクトルを視野角の半分 回転させる
    lookatplus += eyepos;
    // 視野の下限ベクトルを求める
    mtx = mtx.CreateRotationY(-fov / 2.0f);// 視野角の半分を指定して行列を作成
    lookatminus = v.Transform(v, mtx);// 視線ベクトルを視野角の半分 回転させる
    lookatminus += eyepos;
    // 上限ベクトルと点の距離を求める
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

    // 下限ベクトルと点の距離を求める
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
    // 中心座標が視野範囲内か？ をチェックする
    sts = IsInView(eyepos,lookat,fov,circlecenter,length);

    return sts;
}

float Enemy::calcPointLineDist(const DirectX::SimpleMath::Vector3& point, const Segment& segment, DirectX::SimpleMath::Vector3& intersectionpoint, float& t)
{
    float distance = 0.0f;

    //線分のベクトル
    double ABx = segment.endpoint.x - segment.startpoint.x;
    double ABy = segment.endpoint.y - segment.startpoint.y;
    double ABz = segment.endpoint.z - segment.startpoint.z;


    //線分の視点と点を結ぶベクトル
    double APx = point.x - segment.startpoint.x;
    double APy = point.y - segment.startpoint.y;
    double APz = point.z - segment.startpoint.z;

    //線分ABの長さを求める
    double AB2 = ABx * ABx + ABy * ABy + ABz * ABz;

    double ABdotAP = ABx * APx + ABy * APy + ABz * APz;

    //ABベクトルとAPベクトルの内積を計算
    double tt = ABdotAP / AB2;

    //垂線の足
    intersectionpoint.x = static_cast<float>(segment.startpoint.x + ABx * tt);
    intersectionpoint.y = static_cast<float>(segment.startpoint.y + ABy * tt);
    intersectionpoint.z = static_cast<float>(segment.startpoint.z + ABz * tt);

    t = static_cast<float>(tt);

    //垂線の足の長さ
    distance = (intersectionpoint - point).Length();

    return distance;
}

float Enemy::calcPointSegmentDist(const DirectX::SimpleMath::Vector3& p, const Segment& segment, DirectX::SimpleMath::Vector3& intersectionpoint, float& t)
{
    float distance = calcPointLineDist(p, segment, intersectionpoint, t);

    // 交点が線分の外にある（始点に近い）
    if (t < 0.0f) {

        intersectionpoint = segment.startpoint;		// 開始点が交点

        float l = (p - intersectionpoint).Length();	// 交点との距離を求める

        return l;
    }

    // 交点が線分の外にある（終点に近い）
    if (t > 1.0f) {

        intersectionpoint = segment.endpoint;		// 終点が交点

        float l = (p - intersectionpoint).Length();	// 交点との距離を求める

        return l;
    }

    // 交点が線分上にある（０＜ｔ＜１）
    return distance;
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
    DirectX::SimpleMath::Vector3 direction = targetPos - currentPosition;
    float distance = direction.Length();

    // 次の位置に到達した場合の判定を緩める
    float tolerance = MoveSpeed * 2.5f;
    if (distance < tolerance) {
        // 次の位置に到達した場合
        this->SetPosition(targetPos);
        currentwanderingpathIndex++;
        //this->SetState(EStateType::Lookaround);
    }
    else {
        // 移動量を正規化して速度を掛ける
        direction.Normalize();
        this->SetPosition(currentPosition + direction * MoveSpeed);
    }

     //進行方向に向けて回転を更新
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
            this->SethearSound(false);
            this->bookRead = true;
          return;
        }
        //徘徊ルートに戻ったら
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
}

bool Enemy::RayLookHit()
{
    // プレイヤーに向かってレイを飛ばす
    rayDirection = playerdate->GetPosition() - this->GetPosition();
    Vector3 Epos = this->GetPosition();
    // レイの発射位置をY軸方向に少し高くする
    if (playerdate->GetStand())
    {
        Epos.y += StandrayY;
    }
    else if (!playerdate->GetStand())
    {
        Epos.y += SneakrayY;
    }
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
    Epos.y += 45.0f;
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

#include "EnemyManager.h"
#include "Player.h"
#include "BoxObj.h"
#include <algorithm>
#include "TerrainLoder.h"
#include "GUI.h"
#include <cmath>

using namespace DirectX::SimpleMath;

// コンストラクタ（グリッドを受け取る）
EnemyManager::EnemyManager(const std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>> wandering, const std::vector<std::vector<int>> para)
    : grid(grid), Wandering(wandering), astar(grid),parameter(para)
{

}

EnemyManager::~EnemyManager() {
    // メモリ解放
    for (Enemy* enemy : enemies) {
        delete enemy;
        enemy = nullptr;
    }
    enemies.clear();
}


void EnemyManager::AddEnemy(Enemy* enemy) {
    enemies.push_back(enemy);
}

void EnemyManager::EnemysAnimUpdate()
{
    for (Enemy* enemy : enemies)
    {
        enemy->AnimUpdate();
    }
}

void EnemyManager::UpdateEnemies(Player* Pl, const std::vector<BoxObj*>& obstacleBoxes) {

    for (Enemy* enemy : enemies) {
        //敵の視野範囲の判定


        //音が鳴った時
        if (Pl->GetKnockSound() && !enemy->GethearSound() && (enemy->GetState() == EStateType::Patrolling || enemy->GetState() == EStateType::Turn || enemy->GetState() == EStateType::Fixed || enemy->GetState() == EStateType::FixedLeft))
        {
            //音が聞こえる範囲にいるか？
            //if (CCollision::PointInCircle(Pl->GetPosition(), enemy->Gethearrange(), enemy->GetPosition()) /*&& !enemy->GethearSound() && !enemy->GetRookBook() && !enemy->GetbookRead() && !enemy->Getback()*/)
            if(EnemyPathsSound(enemy,Pl->GetPosition()))
            {
                this->EnemyPathsAster(enemy, Pl->GetPosition());
                Pl->SetknockSound(false);
                enemy->SethearSound(true);
                enemy->ChangeState(EStateType::Serch);
            }
        }
        else
        {
            Pl->SetknockSound(false);
        }

        if (enemy->GetState() == EStateType::Back)
        {
            if (enemy->GetTypeSecrity())
            {
                this->EnemyPathsAster(enemy, enemy->GetStartPositon());
            }
            else
            {
                this->EnemyPathsAster(enemy, enemy->GetwanderingPath()[0]);
            }
        }

        //なんとなく見えている距離
        if (enemy->InInViewCircle(enemy->GetPosition(), enemy->PositionForward(), enemy->GetFov(), Pl->GetPosition(), 10.0f, enemy->Getlength() * 1.5f) && !enemy->GetbookRead())
        {
            if (enemy->RayLookHit())
            {
                EnemyPathsAster(enemy, Pl->GetPosition());
                enemy->ChangeState(EStateType::Serch);
                enemy->SetSearch(true);
            }
        }
        //絶対に見つかる距離
        if (enemy->InInViewCircle(enemy->GetPosition(), enemy->PositionForward(), enemy->GetFov(), Pl->GetPosition(),10.0f,enemy->Getlength()) && !enemy->GetbookRead())
        {
            if (enemy->RayLookHit())
            {
                enemy->SetTest(true);
                this->Rook = true;
            }
        }
        else {
            enemy->SetTest(false);
        }

        if (enemy->IsInView(enemy->GetPosition(), enemy->PositionForward(), enemy->GetFov(), Pl->GetBookpos(), enemy->Getlength() * 1.5f) && enemy->GetbookCount() == 0)
        {
            if (enemy->RayLookBook(Pl->GetBookpos(), Pl->GetBooksquare()))
            {
                EnemyPathsAster(enemy, Pl->GetBookpos());
                enemy->ChangeState(EStateType::Bookconnection);
                enemy->SetbookCount(1);
            }
        }

        if (enemy->GetTest())
        {
            this->Rook = true;
        }



        enemy->Update();

    }

}

void EnemyManager::DrawEnemies() {
    for (Enemy* enemy : enemies) {
        enemy->Draw();
    }
}

std::vector<Enemy*> EnemyManager::GetEnemiesWhoSawPlayer() const{
    std::vector<Enemy*> enemiesWhoSawPlayer;
    for (Enemy* enemy : enemies) {
        if (enemy->GetTest()) {
            enemiesWhoSawPlayer.push_back(enemy);
        }
    }
    return enemiesWhoSawPlayer;
}
//敵全体にAsterのパスを渡す
void EnemyManager::UpdateEnemyPaths(const DirectX::SimpleMath::Vector3& playerPosition) {
    for (Enemy* enemy : enemies) {
        
        //グリッド座標にする
        int start_x = static_cast<int>(std::round(std::abs(enemy->GetPosition().x - ORIGIN_TILE_POS_X) / 25.0f));
        int start_y = static_cast<int>(std::round(std::abs(enemy->GetPosition().z - ORIGIN_TILE_POS_Z) / 25.0f));

        int goal_x = static_cast<int>(std::round(std::abs(playerPosition.x - ORIGIN_TILE_POS_X) / 25.0f));
        int goal_y = static_cast<int>(std::round(std::abs(playerPosition.z - ORIGIN_TILE_POS_Z) / 25.0f));

        // グリッド座標をAStarVec2に変換
        AStarVec2 start(start_y, start_x);
        AStarVec2 goal(goal_y, goal_x);

        // A*アルゴリズムを使って経路を計算
        std::vector<AStarNode> path = astar.findPath(start, goal);

        // 経路が見つかった場合、敵に経路をセット
        if (!path.empty()) {
            // 経路をワールド座標に変換して設定
            std::vector<DirectX::SimpleMath::Vector3> worldPath;
            for (const AStarNode& node : path) {
                DirectX::SimpleMath::Vector3 worldPos;
                worldPos.x = node.position.z * 25.0f + ORIGIN_TILE_POS_X;
                worldPos.z = node.position.x * 25.0f + ORIGIN_TILE_POS_Z;
                worldPos.z *= -1;
                worldPos.y = enemy->GetPosition().y;
                worldPath.push_back(worldPos);
            }
            // 経路を設定
            enemy->SetPath(worldPath);
        }
    }
}
//敵単体
void EnemyManager::EnemyPathsAster(Enemy* enemy , const DirectX::SimpleMath::Vector3& playerPosition)
{
    //グリッド座標にする
    int start_x = static_cast<int>(std::round(std::abs(enemy->GetPosition().x - ORIGIN_TILE_POS_X) / SIZEX));
    int start_y = static_cast<int>(std::round(std::abs(enemy->GetPosition().z - ORIGIN_TILE_POS_Z) / SIZEZ));

    int goal_x = static_cast<int>(std::round(std::abs(playerPosition.x - ORIGIN_TILE_POS_X) / SIZEX));
    int goal_y = static_cast<int>(std::round(std::abs(playerPosition.z - ORIGIN_TILE_POS_Z) / SIZEZ));

    // グリッド座標をAStarVec2に変換
    AStarVec2 start(start_y, start_x);
    AStarVec2 goal(goal_y, goal_x);

    // A*アルゴリズムを使って経路を計算
    std::vector<AStarNode> path = astar.findPath(start, goal);

    // 経路が見つかった場合、敵に経路をセット
    if (!path.empty()) {
        // 経路をワールド座標に変換して設定
        std::vector<DirectX::SimpleMath::Vector3> worldPath;
        for (const AStarNode& node : path) {
            DirectX::SimpleMath::Vector3 worldPos;
            worldPos.x = node.position.z * SIZEX + ORIGIN_TILE_POS_X;
            worldPos.z = node.position.x * SIZEZ + ORIGIN_TILE_POS_Z;
            worldPos.z *= -1;
            worldPos.y = enemy->GetPosition().y;
            worldPath.push_back(worldPos);
        }
        // 経路を設定
        enemy->SetPath(worldPath);
    }
}

bool EnemyManager::EnemyPathsSound(Enemy* enemy, const DirectX::SimpleMath::Vector3& playerPosition)
{
    // グリッド座標に変換
    int start_x = static_cast<int>(std::round(std::abs(enemy->GetPosition().x - ORIGIN_TILE_POS_X) / SIZEX));
    int start_y = static_cast<int>(std::round(std::abs(enemy->GetPosition().z - ORIGIN_TILE_POS_Z) / SIZEZ));

    int goal_x = static_cast<int>(std::round(std::abs(playerPosition.x - ORIGIN_TILE_POS_X) / SIZEX));
    int goal_y = static_cast<int>(std::round(std::abs(playerPosition.z - ORIGIN_TILE_POS_Z) / SIZEZ));

    // グリッド座標をAStarVec2に変換
    AStarVec2 start(start_y, start_x);
    AStarVec2 goal(goal_y, goal_x);

    // 音の減衰計算
    float initialVolume = 100.0f;       // 初期音量
    float attenuationRate = 0.1f;        // 1マスごとに10%減衰
    float minThreshold = 10.0f;          // 到達判定の閾値

    // 音が到達するか判定
    bool isReachable = astar.isSoundReachable(start, goal, initialVolume, attenuationRate, minThreshold);

    return isReachable;

}

void EnemyManager::ShadowDraw()
{
    for (Enemy* enemy : enemies)
    {
        enemy->ShadowDraw();
    }
}

void EnemyManager::SetEnemywandering()
{
        for (int i = 0 ; i < Wandering.size() ; i++)
        {
            std::vector<Vector3> worldPositions;
            for (int x = 0; x < (Wandering[i].size() / 3); x++)
            {
                int a = 0;
                // グリッド座標を取得
                pointIndex = Wandering[i][a = x * 3];

                float gridX = static_cast<float>(Wandering[i][a + 1]);
                float gridZ = static_cast<float>(Wandering[i][a + 2]);
                //値が１００じゃないなら巡回パターンの設定
                if (pointIndex != 100)
                {
                    // ワールド座標に変換
                    float worldX = gridX * SIZEX + ORIGIN_TILE_POS_X;
                    float worldZ = gridZ * SIZEZ + ORIGIN_TILE_POS_Z;
                    worldZ *= -1;
                    // ワールド座標をVector3として格納
                    Vector3 worldPosition(worldX, 0.0f, worldZ); // Y座標は0と仮定
                    worldPositions.push_back(worldPosition);
                }
                //値が１００なら巡回パターンの設定
                else if (pointIndex == 100)
                {
                    float FovX = gridX / 100.0f;
                    float FovZ = gridZ / 100.0f;

                    // ワールド座標をVector3として格納
                    Vector3 worldPosition(FovX, 0.0f, FovZ); // Y座標は0と仮定
                    worldPositions.push_back(worldPosition);
                }
            }
            if (pointIndex != 100)
            {
                // 変換されたワールド座標をエネミーに設定
                enemies[i]->SetwanderingPath(worldPositions);
                //ビヘイビアツリーの構築
                enemies[i]->EnemyAIInit(pointIndex);


            }
            else if (pointIndex == 100)
            {
                //見渡す方向を設定
                enemies[i]->Getsecurityfov(worldPositions);
                //ビヘイビアツリーの構築
                enemies[i]->EnemyAIInit(pointIndex);
            }
        }

}

void EnemyManager::SetEnemyParameter()
{
    for (int i = 0; i < parameter.size(); i++)
    {
        std::vector<Vector3> worldPositions;
        for (int x = 0; x < parameter[i].size(); x++)
        {
            //スピードのセット
            if (x == 0)
            {
                float Mspeed = static_cast<float>(parameter[i][x]);
                Mspeed = (Mspeed / 10.0f);
                enemies[i]->SetMoveSpeed(Mspeed);
            }
            //視野角のセット
            else if (x == 1)
            {
                float vAngle = static_cast<float>(parameter[i][x]);
                vAngle = (vAngle / 10.0f);
                enemies[i]->SetFov(vAngle);
            }
            //視野の半径
            else if (x == 2)
            {
                float length = static_cast<float>(parameter[i][x]);
                length = (length / 10.0f);
                enemies[i]->Setlength(length);
            }
            //目線の高さの設定
            else if (x == 3)
            {
                float rayY = static_cast<float>(parameter[i][x]);
                rayY = (rayY / 10.0f);
                enemies[i]->SetStandrayY(rayY);
            }
            //プレイヤーがしゃがんでいるときの目線の高さの設定
            else if (x == 4)
            {
                float rayY = static_cast<float>(parameter[i][x]);
                rayY = (rayY / 10.0f);
                enemies[i]->SetSneakrayY(rayY);
            }
            //本を読む時間の設定
            else if (x == 5)
            {
                float ReadTime = static_cast<float>(parameter[i][x]);
                ReadTime = (ReadTime / 10.0f);
                enemies[i]->SetBookReadTime(ReadTime);
            }
            //音が聞こえる範囲の設定
            else if (x == 6)
            {
                float range = static_cast<float>(parameter[i][x]);
                range = (range / 10.0f);
                enemies[i]->Sethearrange(range);
            }
        }
    }
}

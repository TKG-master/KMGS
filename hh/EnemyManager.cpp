#include "EnemyManager.h"
#include "Player.h"
#include "BoxObj.h"
#include <algorithm>
#include "TerrainLoder.h"
#include "GUI.h"
#include <cmath>

using namespace DirectX::SimpleMath;

// コンストラクタ（グリッドを受け取る）
EnemyManager::EnemyManager(const std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>> wandering)
    : grid(grid), Wandering(wandering), astar(grid)
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

void EnemyManager::EnemyModelInit(std::string ModelName, std::string TexFolderPath)
{
    // アニメーションメッシュ読み込み
    m_AnimationMesh.Load(ModelName, TexFolderPath);
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
        enemy->Update();
        //敵の視野範囲の判定

        //なんとなく見えている距離
        if (enemy->IsInView(enemy->GetPosition(), enemy->PositionForward(), enemy->GetFov(), Pl->GetPosition(), enemy->Getlength() * 1.5f))
        {
            if (enemy->RayLookHit())
            {
                EnemyPathsAster(enemy, Pl->GetPosition());
                enemy->SetSearch(true);
            }
        }
        //絶対に見つかる距離
        if (enemy->IsInView(enemy->GetPosition(), enemy->PositionForward(), enemy->GetFov(), Pl->GetPosition(), enemy->Getlength()))
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

        if (enemy->IsInView(enemy->GetPosition(), enemy->PositionForward(), enemy->GetFov(), Pl->GetBookpos(), enemy->Getlength() * 1.5f) && enemy->GetbookCount() == 0 )
        {
            if (enemy->RayLookBook(Pl->GetBookpos(),Pl->GetBooksquare()))
            {
                EnemyPathsAster(enemy, Pl->GetBookpos());
            }
        }

        //音が鳴った時かつ敵の状態がAlerted以外の時
        if (Pl->GetKnockSound() && enemy->GetState() != EStateType::Lookaround)
        {
            //音が聞こえる範囲にいるか？
            if (CCollision::PointInCircle(Pl->GetPosition(), 500.0f, enemy->GetPosition()) && !enemy->GethearSound())
            {
                this->EnemyPathsAster(enemy, Pl->GetPosition());
                Pl->SetknockSound(false);
                enemy->SethearSound(true);
                enemy->SetSearch(true);
            }
        }

        if (enemy->Getback())
        {
            if (enemy->GetState() == EStateType::Fixed)
            {
                this->EnemyPathsAster(enemy, enemy->GetStartPositon());
            }
            else
            {
                this->EnemyPathsAster(enemy, enemy->GetwanderingPath()[0]);
            }
        }
    }

}

void EnemyManager::DrawEnemies() {
    for (Enemy* enemy : enemies) {
        enemy->Draw();
    }
}

void EnemyManager::DrawEnemiesUI()
{
    for (Enemy* enemy : enemies) {
        enemy->UIDraw();
    }
}

void EnemyManager::NotifyEnemies(Enemy* alertingEnemy) {
    for (Enemy* enemy : enemies) {
        if (enemy != alertingEnemy) {
            enemy->SetState(EStateType::Lookaround);
        }
    }
}

void EnemyManager::AlertEnemies(Enemy* alertedEnemy) {
    for (Enemy* enemy : enemies) {
        if (enemy != alertedEnemy) {
            enemy->SetState(EStateType::Lookaround);
        }
    }
}

void EnemyManager::ManageEnemyState(Enemy* enemy, bool find, const DirectX::SimpleMath::Vector3 PlPos) {
    switch (enemy->GetState()) {
    case EStateType::Patrolling:
        if (Rook) {
            enemy->SetState(EStateType::Lookaround);
            NotifyEnemies(enemy);
        }
        break;
    case EStateType::Lookaround:
        if (Rook)
        {
            this->UpdateEnemyPaths(PlPos);
        }
        break;
    case EStateType::Turn:
        break;
    }
}

std::vector<Enemy*> EnemyManager::GetEnemiesWhoSawPlayer() {
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
            }
            else if (pointIndex == 100)
            {
                enemies[i]->Getsecurityfov(worldPositions);
            }
        }

}

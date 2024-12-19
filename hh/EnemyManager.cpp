#include "EnemyManager.h"
#include "Player.h"
#include "BoxObj.h"
#include <algorithm>
#include "TerrainLoder.h"
#include "GUI.h"
#include <cmath>

using namespace DirectX::SimpleMath;

// �R���X�g���N�^�i�O���b�h���󂯎��j
EnemyManager::EnemyManager(const std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>> wandering)
    : grid(grid), Wandering(wandering), astar(grid)
{

}

EnemyManager::~EnemyManager() {
    // ���������
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
        enemy->Update();
        //�G�̎���͈͂̔���

        //�Ȃ�ƂȂ������Ă��鋗��
        if (enemy->IsInView(enemy->GetPosition(), enemy->PositionForward(), enemy->GetFov(), Pl->GetPosition(), enemy->Getlength() * 1.5f))
        {
            EnemyPathsAster(enemy,Pl->GetPosition());
            enemy->SetSearch(true);
        }
        //��΂Ɍ����鋗��
        if (enemy->IsInView(enemy->GetPosition(), enemy->PositionForward(), enemy->GetFov(), Pl->GetPosition(), enemy->Getlength()) && enemy->GetState() == EStateType::Patrolling)
        {
            enemy->SetTest(true);
            this->Rook = true;
        }
        else {
            enemy->SetTest(false);
        }
        //�������������G�̏�Ԃ�Alerted�ȊO�̎�
        if (Pl->GetKnockSound() && enemy->GetState() != EStateType::Lookaround)
        {
            //������������͈͂ɂ��邩�H
            if (CCollision::PointInCircle(Pl->GetPosition(), 50.0f, enemy->GetPosition()) && !enemy->GethearSound())
            {
                this->EnemyPathsAster(enemy, Pl->GetPosition());
                enemy->SethearSound(true);
                enemy->SetSearch(true);
            }
        }

        if (enemy->Getback())
        {
            this->EnemyPathsAster(enemy,Pl->GetPosition());
        }
        Pl->SetknockSound(false);
    }

}

void EnemyManager::DrawEnemies() {
    for (Enemy* enemy : enemies) {
        enemy->Draw();
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
//�G�S�̂�Aster�̃p�X��n��
void EnemyManager::UpdateEnemyPaths(const DirectX::SimpleMath::Vector3& playerPosition) {
    for (Enemy* enemy : enemies) {
        
        //�O���b�h���W�ɂ���
        int start_x = static_cast<int>(std::round(std::abs(enemy->GetPosition().x - ORIGIN_TILE_POS_X) / SIZEX));
        int start_y = static_cast<int>(std::round(std::abs(enemy->GetPosition().z - ORIGIN_TILE_POS_Z) / SIZEZ));

        int goal_x = static_cast<int>(std::round(std::abs(playerPosition.x - ORIGIN_TILE_POS_X) / SIZEX));
        int goal_y = static_cast<int>(std::round(std::abs(playerPosition.z - ORIGIN_TILE_POS_Z) / SIZEZ));

        // �O���b�h���W��AStarVec2�ɕϊ�
        AStarVec2 start(start_y, start_x);
        AStarVec2 goal(goal_y, goal_x);

        // A*�A���S���Y�����g���Čo�H���v�Z
        std::vector<AStarNode> path = astar.findPath(start, goal);

        // �o�H�����������ꍇ�A�G�Ɍo�H���Z�b�g
        if (!path.empty()) {
            // �o�H�����[���h���W�ɕϊ����Đݒ�
            std::vector<DirectX::SimpleMath::Vector3> worldPath;
            for (const AStarNode& node : path) {
                DirectX::SimpleMath::Vector3 worldPos;
                worldPos.x = node.position.z * SIZEX + ORIGIN_TILE_POS_X;
                worldPos.z = node.position.x * SIZEZ + ORIGIN_TILE_POS_Z;
                worldPos.z *= -1;
                worldPos.y = enemy->GetPosition().y;
                worldPath.push_back(worldPos);
            }
            // �o�H��ݒ�
            enemy->SetPath(worldPath);
        }
    }
}
//�G�P��
void EnemyManager::EnemyPathsAster(Enemy* enemy , const DirectX::SimpleMath::Vector3& playerPosition)
{
    //�O���b�h���W�ɂ���
    int start_x = static_cast<int>(std::round(std::abs(enemy->GetPosition().x - ORIGIN_TILE_POS_X) / SIZEX));
    int start_y = static_cast<int>(std::round(std::abs(enemy->GetPosition().z - ORIGIN_TILE_POS_Z) / SIZEZ));

    int goal_x = static_cast<int>(std::round(std::abs(playerPosition.x - ORIGIN_TILE_POS_X) / SIZEX));
    int goal_y = static_cast<int>(std::round(std::abs(playerPosition.z - ORIGIN_TILE_POS_Z) / SIZEZ));

    // �O���b�h���W��AStarVec2�ɕϊ�
    AStarVec2 start(start_y, start_x);
    AStarVec2 goal(goal_y, goal_x);

    // A*�A���S���Y�����g���Čo�H���v�Z
    std::vector<AStarNode> path = astar.findPath(start, goal);

    // �o�H�����������ꍇ�A�G�Ɍo�H���Z�b�g
    if (!path.empty()) {
        // �o�H�����[���h���W�ɕϊ����Đݒ�
        std::vector<DirectX::SimpleMath::Vector3> worldPath;
        for (const AStarNode& node : path) {
            DirectX::SimpleMath::Vector3 worldPos;
            worldPos.x = node.position.z * SIZEX + ORIGIN_TILE_POS_X;
            worldPos.z = node.position.x * SIZEZ + ORIGIN_TILE_POS_Z;
            worldPos.z *= -1;
            worldPos.y = enemy->GetPosition().y;
            worldPath.push_back(worldPos);
        }
        // �o�H��ݒ�
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
                // �O���b�h���W���擾
                int pointIndex = Wandering[i][a = x * 3];
                float gridX = static_cast<float>(Wandering[i][a + 1]);
                float gridZ = static_cast<float>(Wandering[i][a + 2]);

                // ���[���h���W�ɕϊ�
                float worldX = gridX * SIZEX + ORIGIN_TILE_POS_X;
                float worldZ = gridZ * SIZEZ + ORIGIN_TILE_POS_Z;
                worldZ *= -1;

                // ���[���h���W��Vector3�Ƃ��Ċi�[
                Vector3 worldPosition(worldX, 0.0f, worldZ); // Y���W��0�Ɖ���
                worldPositions.push_back(worldPosition);
            }
            // �ϊ����ꂽ���[���h���W���G�l�~�[�ɐݒ�
            enemies[i]->SetwanderingPath(worldPositions);
        }
}

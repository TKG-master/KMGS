#include "EnemyManager.h"
#include "Player.h"
#include "BoxObj.h"
#include <algorithm>
#include "TerrainLoder.h"
#include "GUI.h"
#include <cmath>

using namespace DirectX::SimpleMath;

// �R���X�g���N�^�i�O���b�h���󂯎��j
EnemyManager::EnemyManager(const std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>> wandering, const std::vector<std::vector<int>> para)
    : grid(grid), Wandering(wandering), astar(grid),parameter(para)
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
        //�G�̎���͈͂̔���


        //����������
        if (Pl->GetKnockSound() && !enemy->GethearSound() && (enemy->GetState() == EStateType::Patrolling || enemy->GetState() == EStateType::Turn || enemy->GetState() == EStateType::Fixed || enemy->GetState() == EStateType::FixedLeft))
        {
            //������������͈͂ɂ��邩�H
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

        //�Ȃ�ƂȂ������Ă��鋗��
        if (enemy->InInViewCircle(enemy->GetPosition(), enemy->PositionForward(), enemy->GetFov(), Pl->GetPosition(), 10.0f, enemy->Getlength() * 1.5f) && !enemy->GetbookRead())
        {
            if (enemy->RayLookHit())
            {
                EnemyPathsAster(enemy, Pl->GetPosition());
                enemy->ChangeState(EStateType::Serch);
                enemy->SetSearch(true);
            }
        }
        //��΂Ɍ����鋗��
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
//�G�S�̂�Aster�̃p�X��n��
void EnemyManager::UpdateEnemyPaths(const DirectX::SimpleMath::Vector3& playerPosition) {
    for (Enemy* enemy : enemies) {
        
        //�O���b�h���W�ɂ���
        int start_x = static_cast<int>(std::round(std::abs(enemy->GetPosition().x - ORIGIN_TILE_POS_X) / 25.0f));
        int start_y = static_cast<int>(std::round(std::abs(enemy->GetPosition().z - ORIGIN_TILE_POS_Z) / 25.0f));

        int goal_x = static_cast<int>(std::round(std::abs(playerPosition.x - ORIGIN_TILE_POS_X) / 25.0f));
        int goal_y = static_cast<int>(std::round(std::abs(playerPosition.z - ORIGIN_TILE_POS_Z) / 25.0f));

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
                worldPos.x = node.position.z * 25.0f + ORIGIN_TILE_POS_X;
                worldPos.z = node.position.x * 25.0f + ORIGIN_TILE_POS_Z;
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

bool EnemyManager::EnemyPathsSound(Enemy* enemy, const DirectX::SimpleMath::Vector3& playerPosition)
{
    // �O���b�h���W�ɕϊ�
    int start_x = static_cast<int>(std::round(std::abs(enemy->GetPosition().x - ORIGIN_TILE_POS_X) / SIZEX));
    int start_y = static_cast<int>(std::round(std::abs(enemy->GetPosition().z - ORIGIN_TILE_POS_Z) / SIZEZ));

    int goal_x = static_cast<int>(std::round(std::abs(playerPosition.x - ORIGIN_TILE_POS_X) / SIZEX));
    int goal_y = static_cast<int>(std::round(std::abs(playerPosition.z - ORIGIN_TILE_POS_Z) / SIZEZ));

    // �O���b�h���W��AStarVec2�ɕϊ�
    AStarVec2 start(start_y, start_x);
    AStarVec2 goal(goal_y, goal_x);

    // ���̌����v�Z
    float initialVolume = 100.0f;       // ��������
    float attenuationRate = 0.1f;        // 1�}�X���Ƃ�10%����
    float minThreshold = 10.0f;          // ���B�����臒l

    // �������B���邩����
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
                // �O���b�h���W���擾
                pointIndex = Wandering[i][a = x * 3];

                float gridX = static_cast<float>(Wandering[i][a + 1]);
                float gridZ = static_cast<float>(Wandering[i][a + 2]);
                //�l���P�O�O����Ȃ��Ȃ珄��p�^�[���̐ݒ�
                if (pointIndex != 100)
                {
                    // ���[���h���W�ɕϊ�
                    float worldX = gridX * SIZEX + ORIGIN_TILE_POS_X;
                    float worldZ = gridZ * SIZEZ + ORIGIN_TILE_POS_Z;
                    worldZ *= -1;
                    // ���[���h���W��Vector3�Ƃ��Ċi�[
                    Vector3 worldPosition(worldX, 0.0f, worldZ); // Y���W��0�Ɖ���
                    worldPositions.push_back(worldPosition);
                }
                //�l���P�O�O�Ȃ珄��p�^�[���̐ݒ�
                else if (pointIndex == 100)
                {
                    float FovX = gridX / 100.0f;
                    float FovZ = gridZ / 100.0f;

                    // ���[���h���W��Vector3�Ƃ��Ċi�[
                    Vector3 worldPosition(FovX, 0.0f, FovZ); // Y���W��0�Ɖ���
                    worldPositions.push_back(worldPosition);
                }
            }
            if (pointIndex != 100)
            {
                // �ϊ����ꂽ���[���h���W���G�l�~�[�ɐݒ�
                enemies[i]->SetwanderingPath(worldPositions);
                //�r�w�C�r�A�c���[�̍\�z
                enemies[i]->EnemyAIInit(pointIndex);


            }
            else if (pointIndex == 100)
            {
                //���n��������ݒ�
                enemies[i]->Getsecurityfov(worldPositions);
                //�r�w�C�r�A�c���[�̍\�z
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
            //�X�s�[�h�̃Z�b�g
            if (x == 0)
            {
                float Mspeed = static_cast<float>(parameter[i][x]);
                Mspeed = (Mspeed / 10.0f);
                enemies[i]->SetMoveSpeed(Mspeed);
            }
            //����p�̃Z�b�g
            else if (x == 1)
            {
                float vAngle = static_cast<float>(parameter[i][x]);
                vAngle = (vAngle / 10.0f);
                enemies[i]->SetFov(vAngle);
            }
            //����̔��a
            else if (x == 2)
            {
                float length = static_cast<float>(parameter[i][x]);
                length = (length / 10.0f);
                enemies[i]->Setlength(length);
            }
            //�ڐ��̍����̐ݒ�
            else if (x == 3)
            {
                float rayY = static_cast<float>(parameter[i][x]);
                rayY = (rayY / 10.0f);
                enemies[i]->SetStandrayY(rayY);
            }
            //�v���C���[�����Ⴊ��ł���Ƃ��̖ڐ��̍����̐ݒ�
            else if (x == 4)
            {
                float rayY = static_cast<float>(parameter[i][x]);
                rayY = (rayY / 10.0f);
                enemies[i]->SetSneakrayY(rayY);
            }
            //�{��ǂގ��Ԃ̐ݒ�
            else if (x == 5)
            {
                float ReadTime = static_cast<float>(parameter[i][x]);
                ReadTime = (ReadTime / 10.0f);
                enemies[i]->SetBookReadTime(ReadTime);
            }
            //������������͈͂̐ݒ�
            else if (x == 6)
            {
                float range = static_cast<float>(parameter[i][x]);
                range = (range / 10.0f);
                enemies[i]->Sethearrange(range);
            }
        }
    }
}

#pragma once
#include "Enemy.h"
#include "Timer.h"
#include "AStar.h"

class Player;
class BoxObj;

//�V�[���̓G�����ׂĊǗ�����N���X
class EnemyManager
{
private:
    std::vector<Enemy*> enemies; // �V�[�����̂��ׂĂ̓G���i�[����x�N�^�[
    std::vector<std::vector<int>> grid;
    //�G�̜p�j���[�g�̏��
    std::vector<std::vector<int>> Wandering;

    // A*�A���S���Y���𗘗p���邽�߂�AStar�C���X�^���X
    Astar astar;

    //����������true
    bool Rook = false;

    bool RookNow = false;

    DirectX::SimpleMath::Vector3 rayDirection;
    //45�Œ�
    float rayY = 45.0f;

    float hitDis = 0.0f;


public:

    // �R���X�g���N�^�i�O���b�h���󂯎��j
    EnemyManager(const std::vector<std::vector<int>>& grid,const std::vector<std::vector<int>> wandering);

    ~EnemyManager();

    // �G��ǉ�����
    void AddEnemy(Enemy* enemy);

    void AddEnemys(std::vector<Enemy*> Enemies)
    {
        enemies = Enemies;
    }

    void EnemysAnimUpdate();

    // �G���X�V����
    void UpdateEnemies(Player* Pl , const std::vector<BoxObj*>& obstacleBoxes);

    // �G��`�悷��
    void DrawEnemies();

    // �G���m�̒ʐM���Ǘ�����
    void NotifyEnemies(Enemy* alertingEnemy);

    // ����̓G���v���C���[���������ꍇ�ɑ��̓G�ɒʒm����
    void AlertEnemies(Enemy* alertedEnemy);

    // �G�̏�Ԃ��Ǘ�����
    void ManageEnemyState(Enemy* enemy,bool find,const DirectX::SimpleMath::Vector3 PlPos);

    // enemies �x�N�^�[�̃Q�b�^�[�֐���ǉ�
    const std::vector<Enemy*>& GetEnemies() const { return enemies; };

    // �v���C���[���������G�l�~�[���擾����֐�
    std::vector<Enemy*> GetEnemiesWhoSawPlayer();

    bool GetRook() { return this->Rook; };

    bool GetRookNow() { return this->RookNow; };

    void SetrayY(float f) { this->rayY = f; };

    float GetrayY() { return this->rayY; };

    void SetRookNow(bool TF) { this->RookNow = TF; };

    void SetrayDistance(DirectX::SimpleMath::Vector3 rayDis) { this->rayDirection = rayDis; };

    DirectX::SimpleMath::Vector3 GetrayDistance() { return this->rayDirection; };

    // �o�H���v�Z���ēG���X�V����
    void UpdateEnemyPaths(const DirectX::SimpleMath::Vector3& playerPosition);

    void EnemyPathsAster(Enemy* enemy , const DirectX::SimpleMath::Vector3& playerPosition);

    //�p�j���[�g���Z�b�g
    void SetEnemywandering();

};


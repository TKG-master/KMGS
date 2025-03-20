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
    // �V�[�����̂��ׂĂ̓G���i�[����x�N�^�[
    std::vector<Enemy*> enemies;
    std::vector<std::vector<int>> grid;
    //�G�̜p�j���[�g�̏��
    std::vector<std::vector<int>> Wandering;
    //�G�̃p�����[�^�̏��
    std::vector<std::vector<int>> parameter;

    // A*�A���S���Y���𗘗p���邽�߂�AStar�C���X�^���X
    Astar astar;

    //����������true
    bool Rook = false;

    bool RookNow = false;

    DirectX::SimpleMath::Vector3 rayDirection;

    float rayY = 45.0f;

    int pointIndex = 0;

    float hitDis = 0.0f;


public:

    // �R���X�g���N�^�i�O���b�h���󂯎��j
    EnemyManager(const std::vector<std::vector<int>>& grid,const std::vector<std::vector<int>> wandering, const std::vector<std::vector<int>> para);

    ~EnemyManager();

    // �G��ǉ�����
    void AddEnemy(Enemy* enemy);

    void AddEnemys(std::vector<Enemy*> Enemies)
    {
        enemies = Enemies;
    }
    //�A�j���[�V�����̃A�b�v�f�[�g
    void EnemysAnimUpdate();

    // �G���X�V����
    void UpdateEnemies(Player* Pl , const std::vector<BoxObj*>& obstacleBoxes);

    // �G��`�悷��
    void DrawEnemies();

    // enemies �x�N�^�[�̃Q�b�^�[�֐���ǉ�
    const std::vector<Enemy*>& GetEnemies() const { return enemies; };

    // �v���C���[���������G�l�~�[���擾����֐�
    std::vector<Enemy*> GetEnemiesWhoSawPlayer() const;

    bool GetRook() { return this->Rook; };

    bool GetRookNow() { return this->RookNow; };

    void SetrayY(float f) { this->rayY = f; };

    float GetrayY() { return this->rayY; };

    void SetRookNow(bool TF) { this->RookNow = TF; };

    void SetrayDistance(DirectX::SimpleMath::Vector3 rayDis) { this->rayDirection = rayDis; };

    DirectX::SimpleMath::Vector3 GetrayDistance() { return this->rayDirection; };

    // �o�H���v�Z���ēG���X�V����
    void UpdateEnemyPaths(const DirectX::SimpleMath::Vector3& playerPosition);
    //�P�̂̓G�Ɍo�H�̃p�X��n��
    void EnemyPathsAster(Enemy* enemy , const DirectX::SimpleMath::Vector3& playerPosition);
    //���̌������s��
    bool EnemyPathsSound(Enemy* enemy , const DirectX::SimpleMath::Vector3& playerPosition);

    //�e�̕`��
    void ShadowDraw();

    //�G�̍s����ݒ�
    void SetEnemywandering();
    //�p�����[�^�[���Z�b�g
    void SetEnemyParameter();

};


#pragma once
#include "Enemy.h"
#include "Timer.h"
#include "AStar.h"

class Player;
class BoxObj;

//シーンの敵をすべて管理するクラス
class EnemyManager
{
private:
    std::vector<Enemy*> enemies; // シーン内のすべての敵を格納するベクター
    std::vector<std::vector<int>> grid;
    //敵の徘徊ルートの情報
    std::vector<std::vector<int>> Wandering;

    // A*アルゴリズムを利用するためのAStarインスタンス
    Astar astar;

    //見つかったらtrue
    bool Rook = false;

    bool RookNow = false;

    DirectX::SimpleMath::Vector3 rayDirection;
    //45固定
    float rayY = 45.0f;

    float hitDis = 0.0f;


public:

    // コンストラクタ（グリッドを受け取る）
    EnemyManager(const std::vector<std::vector<int>>& grid,const std::vector<std::vector<int>> wandering);

    ~EnemyManager();

    // 敵を追加する
    void AddEnemy(Enemy* enemy);

    void AddEnemys(std::vector<Enemy*> Enemies)
    {
        enemies = Enemies;
    }

    void EnemysAnimUpdate();

    // 敵を更新する
    void UpdateEnemies(Player* Pl , const std::vector<BoxObj*>& obstacleBoxes);

    // 敵を描画する
    void DrawEnemies();

    // 敵同士の通信を管理する
    void NotifyEnemies(Enemy* alertingEnemy);

    // 特定の敵がプレイヤーを見つけた場合に他の敵に通知する
    void AlertEnemies(Enemy* alertedEnemy);

    // 敵の状態を管理する
    void ManageEnemyState(Enemy* enemy,bool find,const DirectX::SimpleMath::Vector3 PlPos);

    // enemies ベクターのゲッター関数を追加
    const std::vector<Enemy*>& GetEnemies() const { return enemies; };

    // プレイヤーを見つけたエネミーを取得する関数
    std::vector<Enemy*> GetEnemiesWhoSawPlayer();

    bool GetRook() { return this->Rook; };

    bool GetRookNow() { return this->RookNow; };

    void SetrayY(float f) { this->rayY = f; };

    float GetrayY() { return this->rayY; };

    void SetRookNow(bool TF) { this->RookNow = TF; };

    void SetrayDistance(DirectX::SimpleMath::Vector3 rayDis) { this->rayDirection = rayDis; };

    DirectX::SimpleMath::Vector3 GetrayDistance() { return this->rayDirection; };

    // 経路を計算して敵を更新する
    void UpdateEnemyPaths(const DirectX::SimpleMath::Vector3& playerPosition);

    void EnemyPathsAster(Enemy* enemy , const DirectX::SimpleMath::Vector3& playerPosition);

    //徘徊ルートをセット
    void SetEnemywandering();

};


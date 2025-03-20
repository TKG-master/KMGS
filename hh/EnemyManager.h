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
    // シーン内のすべての敵を格納するベクター
    std::vector<Enemy*> enemies;
    std::vector<std::vector<int>> grid;
    //敵の徘徊ルートの情報
    std::vector<std::vector<int>> Wandering;
    //敵のパラメータの情報
    std::vector<std::vector<int>> parameter;

    // A*アルゴリズムを利用するためのAStarインスタンス
    Astar astar;

    //見つかったらtrue
    bool Rook = false;

    bool RookNow = false;

    DirectX::SimpleMath::Vector3 rayDirection;

    float rayY = 45.0f;

    int pointIndex = 0;

    float hitDis = 0.0f;


public:

    // コンストラクタ（グリッドを受け取る）
    EnemyManager(const std::vector<std::vector<int>>& grid,const std::vector<std::vector<int>> wandering, const std::vector<std::vector<int>> para);

    ~EnemyManager();

    // 敵を追加する
    void AddEnemy(Enemy* enemy);

    void AddEnemys(std::vector<Enemy*> Enemies)
    {
        enemies = Enemies;
    }
    //アニメーションのアップデート
    void EnemysAnimUpdate();

    // 敵を更新する
    void UpdateEnemies(Player* Pl , const std::vector<BoxObj*>& obstacleBoxes);

    // 敵を描画する
    void DrawEnemies();

    // enemies ベクターのゲッター関数を追加
    const std::vector<Enemy*>& GetEnemies() const { return enemies; };

    // プレイヤーを見つけたエネミーを取得する関数
    std::vector<Enemy*> GetEnemiesWhoSawPlayer() const;

    bool GetRook() { return this->Rook; };

    bool GetRookNow() { return this->RookNow; };

    void SetrayY(float f) { this->rayY = f; };

    float GetrayY() { return this->rayY; };

    void SetRookNow(bool TF) { this->RookNow = TF; };

    void SetrayDistance(DirectX::SimpleMath::Vector3 rayDis) { this->rayDirection = rayDis; };

    DirectX::SimpleMath::Vector3 GetrayDistance() { return this->rayDirection; };

    // 経路を計算して敵を更新する
    void UpdateEnemyPaths(const DirectX::SimpleMath::Vector3& playerPosition);
    //単体の敵に経路のパスを渡す
    void EnemyPathsAster(Enemy* enemy , const DirectX::SimpleMath::Vector3& playerPosition);
    //音の減衰を行う
    bool EnemyPathsSound(Enemy* enemy , const DirectX::SimpleMath::Vector3& playerPosition);

    //影の描画
    void ShadowDraw();

    //敵の行動を設定
    void SetEnemywandering();
    //パラメーターをセット
    void SetEnemyParameter();

};


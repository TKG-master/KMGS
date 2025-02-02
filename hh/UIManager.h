#pragma once
#include "GameUI.h"
#include <map>

class Player;
class Enemy;
class Timer;


class UIManager
{
private:
    // ポインタで管理
    std::map<std::string, GameUI*> uiElements;
    // アクティブなUIの配列
    std::vector<GameUI*> activeUIList;
    //登録用の配列
    std::vector<std::string> activeUI;

public:

    ~UIManager(); // デストラクタでメモリ解放
    void AddUI(const std::string& id, GameUI* ui);  // UIを登録
    GameUI* GetUI(const std::string& id);           // UIを取得
    void SetActiveUI(const std::vector<std::string>& ids); // 複数UIをアクティブにする
    void Draw();                                    // 全UIを描画
    void ListCler();

    void InitEnemyUI(const std::vector<Enemy*>& enemies);
    void EnemyUIActive(const std::vector<Enemy*>& enemies);

    void InitPlayerUI();

    void InitTimeUI();

    void TimeactiveUI(Timer* time);

    void PlayerStateUI(Player* Pl);

    void SetactiveUI(const std::vector<std::string>& ids);


};


#include "UIManager.h"
#include "Enemy.h"
#include <iostream>

using namespace DirectX::SimpleMath;

// デストラクタでメモリ解放
UIManager::~UIManager() {
    for (auto& pair : uiElements) {
        delete pair.second; // GameUI* を delete で解放
    }
}

// UIを登録
void UIManager::AddUI(const std::string& id, GameUI* ui) {
    ui->SetID(id);          // GameUI に識別子を設定
    uiElements[id] = ui;    // UI をマップに登録
    std::cout << "Registered UI with ID: " << id << std::endl;
}

// UIを取得
GameUI* UIManager::GetUI(const std::string& id) {
    if (uiElements.find(id) != uiElements.end()) {
        return uiElements[id];
    }
    return nullptr; // 見つからない場合はnullptrを返す
}

// 複数UIをアクティブにする
void UIManager::SetActiveUI(const std::vector<std::string>& ids) {

    for (const auto& id : ids) {
        if (uiElements.find(id) != uiElements.end()) {
            activeUIList.push_back(uiElements[id]); // アクティブなUIをリストに追加
        }
    }
}

// 全UIを描画
void UIManager::Draw() {
    for (auto& ui : activeUIList) {
        ui->Draw();
    }
}

void UIManager::ListCler()
{
    activeUIList.clear();
}

void UIManager::InitEnemyUI(const std::vector<Enemy*>& enemies)
{
    for (int i = 0; i < enemies.size(); i++) {
        std::string id = "enemy_" + std::to_string(i);
        std::string id2 = "suspicious_" + std::to_string(i);
        GameUI* enemyUI = new GameUI();
        GameUI* suspiciousUI = new GameUI();

        // 敵のUIを設定
        float shift = 150.0f * i;
        enemyUI->Init("assets\\Texture\\EnemyUI.png");
        enemyUI->SetHeight(100.0f);
        enemyUI->SetWidth(100.0f);
        enemyUI->SetCenter(Vector2(1800.0f - shift, 900.0f));

        suspiciousUI->Init("assets\\Texture\\hatenaUI.png");
        suspiciousUI->SetHeight(100.0f);
        suspiciousUI->SetWidth(100.0f);
        suspiciousUI->SetCenter(Vector2(1800.0f - shift, 800.0f));

        // UIManagerに追加
        AddUI(id, enemyUI);
        AddUI(id2, suspiciousUI);
    }
}

void UIManager::EnemyUIActive(const std::vector<Enemy*>& enemies)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        std::string id = "enemy_" + std::to_string(i);
        std::string id2 = "suspicious_" + std::to_string(i);

        this->SetActiveUI({id});

        if (enemies[i]->GetSearch())
        {
            this->SetActiveUI({id2});
        }

    }
}

void UIManager::PlayerStateUI(const Player* Pl)
{
  
}

void UIManager::SetactiveUI(const std::vector<std::string>& ids)
{
    activeUI.clear();
    activeUIList.clear();

    for (const auto& id : ids) {
        // UIが存在する場合のみ
        GameUI* ui = GetUI(id);
        if (ui != nullptr) {
            activeUI.push_back(id);
            activeUIList.push_back(ui);
        }
    }
}


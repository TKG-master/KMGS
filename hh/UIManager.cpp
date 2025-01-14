#include "UIManager.h"
#include "Enemy.h"
#include "Player.h"
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
        std::string id3 = "ReadBook_" + std::to_string(i);
        GameUI* enemyUI = new GameUI();
        GameUI* suspiciousUI = new GameUI();
        GameUI* ReadBookUI = new GameUI();

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

        ReadBookUI->Init("assets\\Texture\\hatopng.png");
        ReadBookUI->SetHeight(50.0f);
        ReadBookUI->SetWidth(50.0f);
        ReadBookUI->SetCenter(Vector2(1800.0f - shift, 800.0f));

        // UIManagerに追加
        AddUI(id, enemyUI);
        AddUI(id2, suspiciousUI);
        AddUI(id3, ReadBookUI);
    }
}

void UIManager::EnemyUIActive(const std::vector<Enemy*>& enemies)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        std::string id = "enemy_" + std::to_string(i);
        std::string id2 = "suspicious_" + std::to_string(i);
        std::string id3 = "ReadBook_" + std::to_string(i);

        this->SetActiveUI({id});

        if (enemies[i]->GetSearch() && !enemies[i]->GetRookBook() && !enemies[i]->GetbookRead())
        {
            this->SetActiveUI({id2});
        }
        else if (enemies[i]->GetbookRead())
        {
            this->SetActiveUI({id3});
        }

    }
}

void UIManager::InitPlayerUI()
{
    GameUI* KeyUI = new GameUI();
    KeyUI->Init("assets\\Texture\\PlayerUI.png");
    KeyUI->SetCenter(Vector2(200.0f, 900.0f));
    KeyUI->SetHeight(250.0f);
    KeyUI->SetWidth(250.0f);
    AddUI("KeyUI", KeyUI);

    GameUI* KeyUI2 = new GameUI();
    KeyUI2->Init("assets\\Texture\\Bookput.png");
    KeyUI2->SetCenter(Vector2(450.0f, 950.0f));
    KeyUI2->SetHeight(125.0f);
    KeyUI2->SetWidth(125.0f);
    AddUI("KeyUI2", KeyUI2);

}



void UIManager::PlayerStateUI(Player* Pl)
{
    if (Pl->GetState() == PStateType::STAND)
    {
        this->SetActiveUI({ "KeyUI","KeyUI2"});
    }
    else if (Pl->GetState() == PStateType::SNEAK)
    {
        this->SetActiveUI({ "KeyUI","KeyUI2" });
    }
    else if (Pl->GetState() == PStateType::STIKY)
    {
        this->SetActiveUI({ "KeyUI","KeyUI2" });
    }
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


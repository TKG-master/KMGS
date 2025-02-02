#pragma once
#include "GameUI.h"
#include <map>

class Player;
class Enemy;
class Timer;


class UIManager
{
private:
    // �|�C���^�ŊǗ�
    std::map<std::string, GameUI*> uiElements;
    // �A�N�e�B�u��UI�̔z��
    std::vector<GameUI*> activeUIList;
    //�o�^�p�̔z��
    std::vector<std::string> activeUI;

public:

    ~UIManager(); // �f�X�g���N�^�Ń��������
    void AddUI(const std::string& id, GameUI* ui);  // UI��o�^
    GameUI* GetUI(const std::string& id);           // UI���擾
    void SetActiveUI(const std::vector<std::string>& ids); // ����UI���A�N�e�B�u�ɂ���
    void Draw();                                    // �SUI��`��
    void ListCler();

    void InitEnemyUI(const std::vector<Enemy*>& enemies);
    void EnemyUIActive(const std::vector<Enemy*>& enemies);

    void InitPlayerUI();

    void InitTimeUI();

    void TimeactiveUI(Timer* time);

    void PlayerStateUI(Player* Pl);

    void SetactiveUI(const std::vector<std::string>& ids);


};


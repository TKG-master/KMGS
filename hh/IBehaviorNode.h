#pragma once

class Enemy;  // �O���錾

class IBehaviorNode {
public:
    virtual bool Execute(Enemy* enemy) = 0; // �G�l�~�[�ɑ΂��ăA�N�V���������s
    virtual ~IBehaviorNode() = default;
};


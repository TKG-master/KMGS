#pragma once

class Enemy;  // 前方宣言

class IBehaviorNode {
public:
    virtual bool Execute(Enemy* enemy) = 0; // エネミーに対してアクションを実行
    virtual ~IBehaviorNode() = default;
};


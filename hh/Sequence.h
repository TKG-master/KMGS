#pragma once
#include "IBehaviorNode.h"
#include <vector>

class Sequence : public IBehaviorNode {
private:
    std::vector<IBehaviorNode*> children;

public:
    void AddChild(IBehaviorNode* child);
    bool Execute(Enemy* enemy) override;

    // children を取得するための getter メソッド
    const std::vector<IBehaviorNode*>& GetChildren() const {
        return children;
    }
};
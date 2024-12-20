#pragma once
#include "IBehaviorNode.h"
#include <vector>

class Selector : public IBehaviorNode {
private:
    std::vector<IBehaviorNode*> children;

public:
    void AddChild(IBehaviorNode* child);
    bool Execute(Enemy* enemy) override;

    void UnInit() {
        for (auto child : children)
        {
            delete child;
            child = nullptr;
        }
    }

};


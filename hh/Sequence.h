#pragma once
#include "IBehaviorNode.h"
#include <vector>

class Sequence : public IBehaviorNode {
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


    // children ‚ğæ“¾‚·‚é‚½‚ß‚Ì getter ƒƒ\ƒbƒh
    const std::vector<IBehaviorNode*>& GetChildren() const {
        return children;
    }
};
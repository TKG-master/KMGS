#pragma once
#include "IBehaviorNode.h"
#include <vector>

class Sequence : public IBehaviorNode {
private:
    std::vector<IBehaviorNode*> children;

public:
    void AddChild(IBehaviorNode* child);
    bool Execute(Enemy* enemy) override;

    // children ���擾���邽�߂� getter ���\�b�h
    const std::vector<IBehaviorNode*>& GetChildren() const {
        return children;
    }
};
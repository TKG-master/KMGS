#include "Sequence.h"

void Sequence::AddChild(IBehaviorNode* child) {
    children.push_back(child);
}

bool Sequence::Execute(Enemy* enemy) {
    for (auto& child : children) {
        if (!child->Execute(enemy)) {
            return false;
        }
    }
    return true;
}

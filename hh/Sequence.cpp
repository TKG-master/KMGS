#include "Sequence.h"

void Sequence::AddChild(IBehaviorNode* child) {
    children.push_back(child);
}

bool Sequence::Execute(Enemy* enemy) {
    bool anySuccess = false;
    for (auto child : children) {
        if (child->Execute(enemy)) {
            anySuccess = true;
        }
    }
    return anySuccess;
}

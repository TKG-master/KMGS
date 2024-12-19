#include "Selector.h"

void Selector::AddChild(IBehaviorNode* child) {
    children.push_back(child);
}

bool Selector::Execute(Enemy* enemy) {
    for (auto child : children) {
        if (child->Execute(enemy)) {
            return true;
        }
    }
    return false;
}
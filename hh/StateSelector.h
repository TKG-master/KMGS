#pragma once
#include "Selector.h"
#include <functional>

class StateSelector : public Selector {

private:
    //��Ԃ𔻒肷��֐�
    std::function<bool(Enemy*)> condition;
public:
    StateSelector(std::function<bool(Enemy*)> cond) : condition(cond) {}

    bool Execute(Enemy* enemy) override {
        //�����������ꍇ�ɂ������s
        if (condition(enemy)) 
        {
            return Selector::Execute(enemy);
        }
        return false;
    }
};


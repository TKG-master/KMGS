#pragma once
#include "Selector.h"
#include <functional>

class StateSelector : public Selector {

private:
    //状態を判定する関数
    std::function<bool(Enemy*)> condition;
public:
    StateSelector(std::function<bool(Enemy*)> cond) : condition(cond) {}

    bool Execute(Enemy* enemy) override {
        //条件が合う場合にだけ実行
        if (condition(enemy)) 
        {
            return Selector::Execute(enemy);
        }
        return false;
    }
};


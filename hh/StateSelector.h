#pragma once
#include "Selector.h"
#include <functional>

class StateSelector : public Selector {

private:
    //ó‘Ô‚ğ”»’è‚·‚éŠÖ”
    std::function<bool(Enemy*)> condition;
public:
    StateSelector(std::function<bool(Enemy*)> cond) : condition(cond) {}

    bool Execute(Enemy* enemy) override {
        //ğŒ‚ª‡‚¤ê‡‚É‚¾‚¯Às
        if (condition(enemy)) 
        {
            return Selector::Execute(enemy);
        }
        return false;
    }
};


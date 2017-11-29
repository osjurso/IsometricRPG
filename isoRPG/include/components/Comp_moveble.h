
#ifndef ISORPG_COMP_MOVEBLE_H
#define ISORPG_COMP_MOVEBLE_H

#include <anax/Component.hpp>

#include "states/state_base.h"

class Movable : public anax::Component
{
public:
    int speed;
    std::string path;
    bool agro = false;
    int agroRage;
    float moveX[320];
    float moveY[320];
    int curent = 0;
};

#endif //ISORPG_COMP_MOVEBLE_H

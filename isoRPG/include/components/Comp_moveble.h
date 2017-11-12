
#ifndef ISORPG_COMP_MOVEBLE_H
#define ISORPG_COMP_MOVEBLE_H

#include <anax/Component.hpp>

#include "states/state_base.h"

class Moveble : public anax::Component
{
public:
    int speed;
};

#endif //ISORPG_COMP_MOVEBLE_H

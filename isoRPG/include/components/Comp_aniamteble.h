#ifndef ISORPG_COMP_MOVEBLE_H
#define ISORPG_COMP_MOVEBLE_H
#include <anax/Component.hpp>

#include "states/state_base.h"

class Animated : public anax::Component
{
public:
    bool animated = true;
};

#endif //ISORPG_COMP_MOVEBLE_H

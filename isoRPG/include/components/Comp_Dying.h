#ifndef ISORPG_COMP_DYING_H
#define ISORPG_COMP_DYING_H


#include <anax/Component.hpp>

#include "states/state_base.h"

class DyingComponent : public anax::Component
{
public:
    bool dying = false;
};


#endif //ISORPG_COMP_DYING_H

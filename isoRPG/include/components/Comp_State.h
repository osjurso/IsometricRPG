#ifndef ISORPG_COMP_STATE_H
#define ISORPG_COMP_STATE_H

#include <anax/Component.hpp>

#include "states/state_base.h"

struct StateComponent : public anax::Component
{
public:
    std::string state;
};
#endif //ISORPG_COMP_STATE_H

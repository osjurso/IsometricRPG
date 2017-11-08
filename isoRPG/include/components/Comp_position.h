#ifndef ISORPG_COMP_POSITION_H
#define ISORPG_COMP_POSITION_H

#include <anax/Component.hpp>

#include "states/state_base.h"

class PositionComponent : public anax::Component
    {
    public:
        float XPos;
        float YPos;
    };

#endif //ISORPG_COMP_POSITION_H

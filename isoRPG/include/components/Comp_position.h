#ifndef ISORPG_COMP_POSITION_H
#define ISORPG_COMP_POSITION_H

#include <anax/Component.hpp>

#include "states/state_base.h"

class PositionComponent : public anax::Component
    {
    public:
        float XPos;
        float YPos;
        float SpriteTop;
        float SpriteLeft;
        //for goblins sprites begin x+45 and y +65 form the left upper corner
    };

#endif //ISORPG_COMP_POSITION_H

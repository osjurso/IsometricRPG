
#ifndef ISORPG_COMP_UI_H
#define ISORPG_COMP_UI_H


#include <anax/Component.hpp>

#include "states/state_base.h"


struct UIComp : public anax::Component
{
public:
    bool UI;
    int xOffset = 0;
    int yOffset = 0;
};
#endif //ISORPG_COMP_UI_H

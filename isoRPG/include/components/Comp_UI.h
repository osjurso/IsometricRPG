
#ifndef ISORPG_COMP_UI_H
#define ISORPG_COMP_UI_H


#include <anax/Component.hpp>

#include "states/state_base.h"


struct UIComp : public anax::Component
{
public:
    bool UI;
    int Xofset = 0;
    int Yofset = 0;
};
#endif //ISORPG_COMP_UI_H

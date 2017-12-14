#ifndef ISORPG_COMP_MENUCHOICE_H
#define ISORPG_COMP_MENUCHOICE_H

#include <anax/Component.hpp>

#include "states/state_base.h"

class MenuChoiceComponent : public anax::Component
{
public:
    std::string choice = "";
    std::string source  = "";
};


#endif //ISORPG_COMP_MENUCHOICE_H

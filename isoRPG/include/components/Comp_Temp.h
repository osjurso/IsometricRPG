//
// Created by Bjornar on 20.11.2017.
//

#ifndef ISORPG_COMP_TEMP_H
#define ISORPG_COMP_TEMP_H
#include <anax/Component.hpp>

#include "states/state_base.h"


struct TempComponent : public anax::Component
{
public:
    bool (*boolfp)();
    void (*voidfunc)(anax::Entity entity);
};

#endif //ISORPG_COMP_TEMP_H

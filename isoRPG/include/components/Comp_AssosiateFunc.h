
#ifndef ISORPG_COMP_ASSOSIATEFUNC_H
#define ISORPG_COMP_ASSOSIATEFUNC_H

#include <anax/Component.hpp>

#include "states/state_base.h"


struct AssosateFunc : public anax::Component
{
public:
    void (*voidfunc)(anax::Entity& entity,anax::Entity& player, anax::World& world);
    void (*voidMenufunc)(anax::Entity& entity);

};

#endif //ISORPG_COMP_ASSOSIATEFUNC_H

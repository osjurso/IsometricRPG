
#ifndef ISORPG_RESOLVE_AGRO_H
#define ISORPG_RESOLVE_AGRO_H


#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <iostream>

#include <components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_movable.h>

struct ResolveAgro
{
public:
    void agro(anax::Entity player, anax::World& world);

};

#endif //ISORPG_RESOLVE_AGRO_H

#ifndef ISORPG_GENERATEPATH_H
#define ISORPG_GENERATEPATH_H

#include <iostream>

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>

#include <systems/pathfinding.h>
#include <components/Comp_position.h>
#include <components/Comp_movable.h>

struct GeneratePath
{
public:

    void generate( anax::World& world, anax::Entity player);
};

#endif //ISORPG_GENERATEPATH_H

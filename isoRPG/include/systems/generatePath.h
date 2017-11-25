
#ifndef ISORPG_GENERATEPATH_H
#define ISORPG_GENERATEPATH_H


#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>
#include <systems/pathfinding.h>
#include <states/state_base.h>
#include <application.h>
#include <iostream>

#include <components/Comp_position.h>
#include <components/Comp_moveble.h>

struct GeneratePath
{
public:

    void generate( anax::World& world, anax::Entity player);
};

#endif //ISORPG_GENERATEPATH_H

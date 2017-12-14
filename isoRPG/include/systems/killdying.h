#ifndef ISORPG_KILLDYING_H
#define ISORPG_KILLDYING_H

#include <iostream>


#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "states/state_base.h"
#include "application.h"
#include <components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <components/Comp_healt.h>
#include <components/Comp_lootable.h>
#include <components/Comp_Dying.h>


class KillDying
{
public:
    void killDying( anax::World& world)
    {
        auto entities = world.getEntities();

        for( auto e : entities)
        {
            if(e.hasComponent<DyingComponent>())
            {
                if(e.getComponent<DyingComponent>().dying)
                {
                    e.kill();
                    world.refresh();
                }
            }
        }
    }
};

#endif //ISORPG_KILLDYING_H

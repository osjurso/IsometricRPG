#ifndef ISORPG_KILLDIALOGS_H
#define ISORPG_KILLDIALOGS_H


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
#include <components/Comp_talk.h>
#include <components/Comp_Children.h>
#include <collections/mouseClickedFunctions.h>

class KillDilogues
{
public:
    void killDialogs(anax::Entity& entity,anax::Entity& player,anax::World& world)
    {
        auto entities = world.getEntities();

        for( auto e : entities)
        {
            if(e.hasComponent<Talkative>())
            {
                if(e.getComponent<Talkative>().activeDialog)
                {
                    killChildren(entity, player, world);
                }
                e.getComponent<Talkative>().activeDialog = false;

            }
        }
    }
};
#endif //ISORPG_KILLDIALOGS_H

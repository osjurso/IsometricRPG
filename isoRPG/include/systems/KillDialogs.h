//
// Created by Bjornar on 12/4/2017.
//

#ifndef ISORPG_KILLDIALOGS_H
#define ISORPG_KILLDIALOGS_H


#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>


#include <include/components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <include/components/Comp_healt.h>
#include <iostream>
#include <include/components/Comp_looteble.h>
#include <include/components/Comp_Dying.h>
#include <include/components/Comp_talk.h>
#include <include/components/Comp_Children.h>
#include <include/collections/mouseClikedFunctions.h>

class KillDilogs
{
public:
    void killDialogs(anax::Entity& entity,anax::Entity& player,anax::World& world)
    {
        auto entitys = world.getEntities();

        for( auto e : entitys)
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

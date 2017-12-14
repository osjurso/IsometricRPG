

#ifndef ISORPG_UPDATEDIALOG_H
#define ISORPG_UPDATEDIALOG_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>


#include <components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <components/Comp_healt.h>
#include <iostream>
#include <components/Comp_lootable.h>
#include <include/components/Comp_UI.h>
#include <include/components/Comp_Changeable.h>
#include <include/components/Comp_ActionTimers.h>
#include <include/components/Comp_talk.h>
#include "talk.h"


class UpdateDialogue
{
public:
    void update(anax::World& world, sf::RenderWindow& window, sf::View cam, float zoom, sf::Font font, sf::Texture& paper, sf::Texture& redX,sf::Texture& arrow)
    {
        auto entities = world.getEntities();

        for(auto i : entities)
        {
            if(i.hasComponent<Talkative>())
            {
                if(i.getComponent<Talkative>().changeDialog)
                {
                    Talk talk;
                    talk.talk(i,window, world,cam ,zoom, font, paper, redX, arrow);
                    i.getComponent<Talkative>().changeDialog = false;
                }

            }
        }
    }
};

#endif //ISORPG_UPDATEDIALOG_H

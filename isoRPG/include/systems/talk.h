//
#ifndef ISORPG_TALK_H
#define ISORPG_TALK_H


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
#include <include/components/Comp_talk.h>
#include <fstream>


class Talk
{
public:

    void talk(anax::Entity speaker, sf::RenderWindow& window)
    {
        Talkative& talkative = speaker.getComponent<Talkative>();
        if(talkative.numberOfDialoges <= 1)
        {
            std::ifstream file(talkative.files[0]);
            std::string str;
            while (std::getline(file, str))
            {
                std::cout << str  << std::endl;
            }
        }
    }
};

#endif //ISORPG_TALK_H

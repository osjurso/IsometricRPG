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
#include <include/collections/drawebleText.h>


class Talk
{
public:

    void talk(anax::Entity& speaker, sf::RenderWindow& window, anax::World& world,sf::View cam, float zoom, sf::Font& font)
    {
        Talkative& talkative = speaker.getComponent<Talkative>();
        DrawebleText drawebleText;
        if(talkative.numberOfDialoges >= 1)
        {
            std::ifstream file(talkative.Talkingfiles[0]);
            std::string str;
            std::string dialogString;
            while (std::getline(file, str))
            {
                dialogString = dialogString + str + " \n ";
            }
            anax::Entity entity = world.createEntity();

            drawebleText.setUpDrawebleText(entity,dialogString,cam,"Game",zoom,font,sf::Color().Black);
            entity.addComponent<MousedOver>();

            entity.getComponent<UIComp>().Xofset = 200;
            entity.getComponent<UIComp>().Yofset = -50;
        }

        if(talkative.numberOfOptions >= 1)
        {
            std::ifstream file2(talkative.Optionfiles[0]);

            std::string str2;
            std::string optionString;

            while (std::getline(file2, str2))
            {
                optionString = str2;
                std::cout << optionString << std::endl;

                anax::Entity option = world.createEntity();

                drawebleText.setUpDrawebleText(option,optionString,cam,"Game", zoom,font,sf::Color().Black);
                option.getComponent<UIComp>().Xofset = 100;
                option.getComponent<UIComp>().Yofset = -50;
                option.addComponent<MousedOver>();
            }
        }
    }
};

#endif //ISORPG_TALK_H

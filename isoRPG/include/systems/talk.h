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
#include <include/components/Comp_AssosiateFunc.h>
#include "collections/mouseClikedFunctions.h"

class Talk
{
public:

    void talk(anax::Entity& speaker, sf::RenderWindow& window, anax::World& world,sf::View cam, float zoom, sf::Font font)
    {
        Talkative& talkative = speaker.getComponent<Talkative>();
        DrawebleText drawebleText;
        int line = 0;
        if(talkative.Talkingfiles.at(talkative.Current) != "")
        {
            std::ifstream file(talkative.Talkingfiles[talkative.Current]);
            std::string str;
            std::string wholestring;
            while (std::getline(file, str))
            {
                wholestring = wholestring + str + " \n ";
                line +=1;
            }
            anax::Entity entity = world.createEntity();
            drawebleText.setUpDrawebleText(entity,wholestring,cam,"Game",zoom,font,sf::Color().Black);
            entity.getComponent<UIComp>().Xofset = 200;
            entity.getComponent<UIComp>().Yofset = -50;
        }
        if(talkative.Optoinfiles.at(talkative.Current) != "")
        {
            std::ifstream file(talkative.Optoinfiles[talkative.Current]);
            std::string str;
            std::string wholestring;
            while (std::getline(file, str))
            {
                wholestring = wholestring + str + " \n ";
                anax::Entity entity = world.createEntity();
                drawebleText.setUpDrawebleText(entity,wholestring,cam,"Game",zoom,font,sf::Color().Black);
                entity.getComponent<UIComp>().Xofset = 200;
                entity.getComponent<UIComp>().Yofset = -50+ line*10;
                line +=1;
                wholestring = "";
                entity.addComponent<MousedOver>();
                entity.addComponent<AssosateFunc>();
                entity.getComponent<AssosateFunc>().voidfunc = printTempVoid;
            }




        }
    }
};

#endif //ISORPG_TALK_H

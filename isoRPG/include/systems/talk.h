
#ifndef ISORPG_TALK_H
#define ISORPG_TALK_H


#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <fstream>

#include <components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <components/Comp_healt.h>
#include <components/Comp_looteble.h>
#include <components/Comp_talk.h>
#include <components/Comp_AssosiateFunc.h>

#include <collections/drawebleText.h>
#include "collections/mouseClikedFunctions.h"
#include <collections/setUpUI.h>
#include <include/components/Comp_Children.h>
#include <include/components/Comp_Dying.h>


class Talk
{
public:

    void talk(anax::Entity& speaker, sf::RenderWindow& window, anax::World& world,sf::View cam, float zoom, sf::Font font, sf::Texture& paperTexture, sf::Texture& redXTexture)
    {
        Talkative& talkative = speaker.getComponent<Talkative>();
        DrawebleText drawebleText;

        anax::Entity redX = world.createEntity();

        redX.addComponent<ChildComponent>();
        ChildComponent& childComponent = redX.getComponent<ChildComponent>();

        anax::Entity paper = world.createEntity();
        Draweble draweble;
        draweble.makeDraweble(paperTexture,0,0,paper,"Game");
        draweble.makeDraweble(redXTexture,500,500,redX,"Game");


        paper.getComponent<TextureComponent>().sprite[0].setScale(zoom,zoom);
        paper.addComponent<UIComp>();
        paper.getComponent<UIComp>().Xofset = 182;
        paper.getComponent<UIComp>().Yofset = -56;
        paper.getComponent<TextureComponent>().sortKey = 1001;
        paper.addComponent<DyingComponent>();

        redX.getComponent<TextureComponent>().sprite[0].setScale(zoom/4,zoom/4);
        redX.addComponent<UIComp>();
        redX.getComponent<UIComp>().Xofset = 378;
        redX.getComponent<UIComp>().Yofset = -56;
        redX.getComponent<TextureComponent>().sortKey = 1002;
        redX.addComponent<MousedOver>();
        redX.addComponent<AssosateFunc>();
        redX.getComponent<AssosateFunc>().voidfunc = killChildren;
        redX.addComponent<DyingComponent>();


        childComponent.children.push_back(paper);

        int line = 0;
        if(talkative.talkingfiles[talkative.Current] != "")
        {
            std::ifstream file(talkative.talkingfiles[talkative.Current]);
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
            entity.getComponent<UIComp>().Yofset = -58;
            entity.addComponent<DyingComponent>();
            childComponent.children.push_back(entity);
        }
        if(talkative.total[talkative.Current] > 0)
        {
            for(int i = 0; i <= talkative.total[talkative.Current]; i++)
            {
                anax::Entity entity = world.createEntity();
                //std::string content = tempStringMap[i];
                std::string content = talkative.optionMap[i];
                drawebleText.setUpDrawebleText(entity,content,cam,"Game",zoom,font,sf::Color().Black);
                entity.getComponent<UIComp>().Xofset = 200;
                entity.getComponent<UIComp>().Yofset = -60+ line*15;
                line +=1;
                entity.addComponent<MousedOver>();
                entity.addComponent<AssosateFunc>();
                entity.getComponent<AssosateFunc>().voidfunc = speaker.getComponent<Talkative>().functionmap[i];
                childComponent.children.push_back(entity);
                entity.addComponent<DyingComponent>();
            }
        }
    }
};

#endif //ISORPG_TALK_H

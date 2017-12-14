
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
#include <components/Comp_lootable.h>
#include <components/Comp_talk.h>
#include <components/Comp_AssosiateFunc.h>

#include <collections/drawableText.h>
#include "collections/mouseClickedFunctions.h"
#include "KillDialogues.h"
#include <collections/setUpUI.h>
#include <include/components/Comp_Children.h>
#include <include/components/Comp_Dying.h>
#include <include/components/Comp_Parent.h>


class Talk
{
public:

    void talk(anax::Entity& speaker, sf::RenderWindow& window, anax::World& world,sf::View cam, float zoom, sf::Font font, sf::Texture& paperTexture, sf::Texture& redXTexture, sf::Texture& arrow)
    {
        //Kill existing dialog
        KillDilogues killDilogues;
        anax::Entity tempEntity;
        killDilogues.killDialogs(speaker,tempEntity,world);


        Talkative& talkative = speaker.getComponent<Talkative>();
        DrawableText drawableText;

        anax::Entity redX = world.createEntity();

        redX.addComponent<ParentComponent>();
        redX.getComponent<ParentComponent>().parent = speaker;

        redX.addComponent<ChildComponent>();
        ChildComponent& childComponent = redX.getComponent<ChildComponent>();

        anax::Entity paper = world.createEntity();
        Drawable drawable;
        drawable.makeDrawable(paperTexture, 0, 0, paper, "Game");
        drawable.makeDrawable(redXTexture, 0, 0, redX, "Game");

        paper.getComponent<TextureComponent>().sprite[0].setScale(zoom,zoom);
        paper.addComponent<UIComp>();
        paper.getComponent<UIComp>().xOffset = 182;
        paper.getComponent<UIComp>().yOffset = -56;
        paper.getComponent<TextureComponent>().sortKey = 5001;
        paper.addComponent<DyingComponent>();

        redX.getComponent<TextureComponent>().sprite[0].setScale(zoom/4,zoom/4);
        redX.getComponent<SizeComponent>().width -= 160;
        redX.getComponent<SizeComponent>().Height -= 153;
        redX.getComponent<SizeComponent>().SpriteWidth = redX.getComponent<SizeComponent>().width;
        redX.getComponent<SizeComponent>().SpriteHeight = redX.getComponent<SizeComponent>().Height;
        redX.addComponent<UIComp>();
        redX.getComponent<UIComp>().xOffset = 378;
        redX.getComponent<UIComp>().yOffset = -56;
        redX.getComponent<TextureComponent>().sortKey = 5002;
        redX.addComponent<MousedOver>();
        redX.addComponent<AssosateFunc>();
        redX.getComponent<AssosateFunc>().voidfunc = killChildren;
        redX.addComponent<DyingComponent>();
        childComponent.children.push_back(paper);

        if (!speaker.hasComponent<ChildComponent>())
        {
            speaker.addComponent<ChildComponent>();
        }

        speaker.getComponent<ChildComponent>().children.push_back(redX);
        speaker.getComponent<ChildComponent>().children.push_back(paper);

        if(speaker.getComponent<Talkative>().Default != -1 && (speaker.getComponent<Talkative>().Default =! speaker.getComponent<Talkative>().Current))
        {
            anax::Entity NextArrow = world.createEntity();
            NextArrow.addComponent<ParentComponent>();

            drawable.makeDrawable(arrow, 0, 0, NextArrow, "Game");
            NextArrow.getComponent<TextureComponent>().sprite[0].setScale(zoom,zoom);
            NextArrow.addComponent<UIComp>();
            NextArrow.getComponent<UIComp>().xOffset = 378;
            NextArrow.getComponent<UIComp>().yOffset = -20;
            NextArrow.getComponent<TextureComponent>().sortKey = 5002;
            NextArrow.addComponent<MousedOver>();
            NextArrow.addComponent<AssosateFunc>();
            NextArrow.getComponent<AssosateFunc>().voidfunc = setDefault;
            NextArrow.addComponent<DyingComponent>();

            childComponent.children.push_back(NextArrow);
            speaker.getComponent<ChildComponent>().children.push_back(NextArrow);
            redX.getComponent<ChildComponent>().children.push_back(NextArrow);
            NextArrow.getComponent<ParentComponent>().parent = redX;
        }

        int line = 0;
        if(talkative.talkingFiles[talkative.Current] != "")
        {
            std::ifstream file(talkative.talkingFiles[talkative.Current]);
            std::string str;
            std::string wholestring;
            while (std::getline(file, str))
            {
                wholestring = wholestring + str + " \n ";
                line +=1;
            }
            anax::Entity entity = world.createEntity();
            drawableText.setUpDrawableText(entity, wholestring, cam, "Game", zoom, font, sf::Color().Black);
            entity.getComponent<UIComp>().xOffset = 190;
            entity.getComponent<UIComp>().yOffset = -58;
            entity.addComponent<DyingComponent>();
            childComponent.children.push_back(entity);
            speaker.getComponent<ChildComponent>().children.push_back(entity);
            entity.getComponent<TextureComponent>().sortKey = 5003;
        }
        if(talkative.total[talkative.Current] > 0)
        {
            for(int i = 0; i <= talkative.total[talkative.Current]; i++)
            {
                anax::Entity entity = world.createEntity();
                std::string content = talkative.optionMap[i + 3*talkative.Current];
                drawableText.setUpDrawableText(entity, content, cam, "Game", zoom, font, sf::Color(40, 20, 20));
                entity.getComponent<UIComp>().xOffset = 190;
                entity.getComponent<UIComp>().yOffset = -60+ line*12;
                line +=1;
                entity.addComponent<MousedOver>();
                entity.addComponent<AssosateFunc>();
                entity.getComponent<AssosateFunc>().voidfunc = speaker.getComponent<Talkative>().functionMap[i+ 3*talkative.Current];
                childComponent.children.push_back(entity);
                entity.addComponent<DyingComponent>();
                speaker.getComponent<ChildComponent>().children.push_back(entity);
                entity.addComponent<ParentComponent>();
                entity.getComponent<ParentComponent>().parent = redX;
                entity.getComponent<TextureComponent>().sortKey = 10000;
            }
        }
    }
};

#endif //ISORPG_TALK_H

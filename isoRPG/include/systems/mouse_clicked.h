
#ifndef ISORPG_MOUSE_CLICKED_H
#define ISORPG_MOUSE_CLICKED_H

#include <anax/System.hpp>
#include <states/state_base.h>


#include <include/components/Comp_size.h>
#include <include/components/Comp_mousedOver.h>
#include <components/Comp_position.h>
#include <iostream>
#include <include/components/Comp_looteble.h>
#include <include/components/Comp_talk.h>
#include "loot.h"
#include "talk.h"

struct MouseClicked : anax::System<anax::Requires<PositionComponent, SizeComponent, MousedOver>>
{
public:
    MouseClicked()
    {}
    void Clicked(anax::World& world, anax::Entity& entity, sf::RenderWindow& window, sf::View cam)
    {
        auto enteties = world.getEntities();

        for(auto i : enteties)
        {
            if(i.hasComponent<MousedOver>())
                process(i,sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y, world, entity, window, cam);
        }
    }


private:
    void process(anax::Entity& e, float MouseX, float MouseY, anax::World& world, anax::Entity player, sf::RenderWindow& window, sf::View cam)
    {
        PositionComponent& positionComponent = e.getComponent<PositionComponent>();
        SizeComponent& sizeComponent = e.getComponent<SizeComponent>();
        sf::IntRect entityRect;
        entityRect.top = positionComponent.SpriteTop;
        entityRect.left = positionComponent.SpriteLeft;
        entityRect.width = sizeComponent.SpriteWhith;
        entityRect.height = sizeComponent.SpriteHeight;

        sf::Vector2i mouse;
        mouse.x = MouseX;
        mouse.y = MouseY;
        sf::Vector2f mouseT= window.mapPixelToCoords(mouse, cam);
        if(entityRect.contains(mouseT.x,mouseT.y))
        {
            if(e.hasComponent<Talkative>())
            {
                std::cout << e.getId() << std::endl;
                Talk talk;
                talk.talk(e,window);
            }

            if(e.hasComponent<Looteble>())
            {
                Loot loot;
                loot.loot(world,e, player);
            }


        }
    }
};

#endif //ISORPG_MOUSE_CLICKED_H

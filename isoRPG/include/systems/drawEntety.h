//
// Created by Bjornar on 02.11.2017.
//

#ifndef ISORPG_DRAWENTETY_H
#define ISORPG_DRAWENTETY_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>


#include <include/components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <include/components/Comp_animation.h>


class DrawEntetys : anax::System<anax::Requires<PositionComponent, SizeComponent>>
{
public:
    DrawEntetys(){}

    void draw(sf::RenderWindow& window, anax::World& world)
    {
        auto enteties = world.getEntities();

        for(auto i : enteties)
        {
            TextureComponent textureComponent  = i.getComponent<TextureComponent>();
            PositionComponent positionComponent = i.getComponent<PositionComponent>();

            if (i.hasComponent<AnimationComponent>()) {
                textureComponent.spriteRect = textureComponent.spriteRect;
            }

            textureComponent.sprite.setPosition(positionComponent.XPos,positionComponent.YPos);
            window.draw(textureComponent.sprite);
        }
    }
};


#endif //ISORPG_DRAWENTETY_H

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
#include <components/Comp_animation.h>
#include <include/components/Comp_State.h>


class DrawEntetys : anax::System<anax::Requires<PositionComponent, SizeComponent>>
{
public:
    DrawEntetys(){}

    void draw(sf::RenderWindow& window, anax::World& world, std::string state)
    {
        auto enteties = world.getEntities();

        for(auto i : enteties)
        {
            StateComponent& stateComponent = i.getComponent<StateComponent>();
            TextureComponent& textureComponent  = i.getComponent<TextureComponent>();
            PositionComponent& positionComponent = i.getComponent<PositionComponent>();

            if(stateComponent.state == state)
            {
                if(i.hasComponent<AnimationComponent>())
                {
                    textureComponent.sprite.setTextureRect(textureComponent.spriteRect);
                }
                SizeComponent sizeComponent = i.getComponent<SizeComponent>();
                sf::RectangleShape rect;
                rect.setPosition(positionComponent.SpriteLeft,positionComponent.SpriteTop);
                sf::Vector2f sice;
                sice.x = sizeComponent.SpriteWhith;
                sice.y = sizeComponent.SpriteHeight;
                rect.setSize(sice);

                textureComponent.sprite.setPosition(positionComponent.XPos,positionComponent.YPos);
                window.draw(textureComponent.sprite);
                //window.draw(rect); // Remove to demonstrate waerd bug

            }
        }
    }
};


#endif //ISORPG_DRAWENTETY_H

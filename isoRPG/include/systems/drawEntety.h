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
                    textureComponent.sprite[0].setTextureRect(textureComponent.spriteRect);
                    if(textureComponent.multisprite)
                    {
                        textureComponent.sprite[1].setTextureRect(textureComponent.spriteRect);
                        textureComponent.sprite[2].setTextureRect(textureComponent.spriteRect);
                        textureComponent.sprite[3].setTextureRect(textureComponent.spriteRect);
                    }
                }

                if(textureComponent.multisprite)
                {
                    textureComponent.sprite[0].setPosition(positionComponent.XPos,positionComponent.YPos);
                    textureComponent.sprite[1].setPosition(positionComponent.XPos,positionComponent.YPos);
                    textureComponent.sprite[2].setPosition(positionComponent.XPos, positionComponent.YPos);
                    textureComponent.sprite[3].setPosition(positionComponent.XPos, positionComponent.YPos);
                    window.draw(textureComponent.sprite[0]);
                    window.draw(textureComponent.sprite[1]);
                    window.draw(textureComponent.sprite[2]);
                    window.draw(textureComponent.sprite[3]);
                }else
                {
                    textureComponent.sprite[0].setPosition(positionComponent.XPos,positionComponent.YPos);
                    window.draw(textureComponent.sprite[0]);
                }
            }
        }
    }
};


#endif //ISORPG_DRAWENTETY_H

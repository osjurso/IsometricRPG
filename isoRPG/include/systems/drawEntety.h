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
                    textureComponent.sHeroBody.setTextureRect(textureComponent.spriteRect);
                    textureComponent.sHeroHead.setTextureRect(textureComponent.spriteRect);
                    textureComponent.sHeroWeapon.setTextureRect(textureComponent.spriteRect);
                    textureComponent.sHeroShield.setTextureRect(textureComponent.spriteRect);
                }
                textureComponent.sHeroBody.setPosition(positionComponent.XPos,positionComponent.YPos);
                textureComponent.sHeroHead.setPosition(positionComponent.XPos,positionComponent.YPos);
                textureComponent.sHeroWeapon.setPosition(positionComponent.XPos, positionComponent.YPos);
                textureComponent.sHeroShield.setPosition(positionComponent.XPos, positionComponent.YPos);
                window.draw(textureComponent.sHeroBody);
                window.draw(textureComponent.sHeroHead);
                window.draw(textureComponent.sHeroWeapon);
                window.draw(textureComponent.sHeroShield);
            }
        }
    }
};


#endif //ISORPG_DRAWENTETY_H

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
#include <include/components/Comp_aniamteble.h>
#include <iostream>


class DrawEntetys : anax::System<anax::Requires<PositionComponent, SizeComponent>>
{
public:
    DrawEntetys(){}


    void draw(sf::RenderWindow& window, anax::World& world)
    {
        auto enteties = world.getEntities();

        for(auto i : enteties)
        {
            TextureComponent& textureComponent  = i.getComponent<TextureComponent>();
            PositionComponent& positionComponent = i.getComponent<PositionComponent>();
            if (i.hasComponent<Animated>()) {
                textureComponent.sprite.setTextureRect(textureComponent.spriteRect);
                std::cout << "x:" << textureComponent.sprite.getTextureRect().top << ", ";
                std::cout << "y:" << textureComponent.sprite.getTextureRect().left << ", ";
                std::cout << "width:" << textureComponent.sprite.getTextureRect().width << ", " ;
                std::cout << "height:" << textureComponent.sprite.getTextureRect().height << ", "<< std::endl;
            }

            textureComponent.sprite.setPosition(positionComponent.XPos,positionComponent.YPos);
            window.draw(textureComponent.sprite);
        }
    }
};

#endif //ISORPG_DRAWENTETY_H

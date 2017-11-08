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


class DrawEntetys : anax::System<anax::Requires<PositionComponent, SizeComponent>>
{
public:
    DrawEntetys(){}

    void draw(sf::RenderWindow& window)
    {
        auto enteties = getEntities();

        for(auto i : enteties)
        {
            TextureComponent textureComponent  = i.getComponent<TextureComponent>();
            window.draw(textureComponent.sprite);
            //process(i, window);
        }
    }
};


#endif //ISORPG_DRAWENTETY_H

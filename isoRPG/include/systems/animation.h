#ifndef ISORPG_ANIMATION_H
#define ISORPG_ANIMATION_H

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


class Animation : anax::System<anax::Requires<PositionComponent, SizeComponent, AnimationComponent>>
{
public:
    Animation(){}

    void animate(sf::RenderWindow& window, anax::World& world)
    {
        auto enteties = world.getEntities();

        for(auto i : enteties)
        {
            TextureComponent &textureComponent = i.getComponent<TextureComponent>();
        }
    }
};

#endif //ISORPG_ANIMATION_H

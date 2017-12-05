#ifndef ISORPG_SORT_KEY_UPDATE_H
#define ISORPG_SORT_KEY_UPDATE_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>


#include <include/components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <include/components/Comp_healt.h>
#include <iostream>
#include <include/components/Comp_looteble.h>
#include <include/components/Comp_moveble.h>


class SortKeyUpdate
{
public:

    void Update(anax::World& world)
    {
        auto entities = world.getEntities();

        for (auto i : entities)
        {
            if (i.hasComponent<Movable>())
            {
                auto& textureComponent = i.getComponent<TextureComponent>();
                auto positionComponent = i.getComponent<PositionComponent>();
                auto sizeComponent = i.getComponent<SizeComponent>();
                i.getComponent<TextureComponent>().sortKey = static_cast<int>(positionComponent.SpriteTop + sizeComponent.SpriteHeight);
            }
        }
    }
};

#endif //ISORPG_SORT_KEY_UPDATE_H

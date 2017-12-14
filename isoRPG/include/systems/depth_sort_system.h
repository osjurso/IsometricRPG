#ifndef ISORPG_SORT_KEY_UPDATE_H
#define ISORPG_SORT_KEY_UPDATE_H

#include <iostream>

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#include "states/state_base.h"
#include "application.h"

#include <components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <components/Comp_healt.h>
#include <components/Comp_lootable.h>
#include <components/Comp_movable.h>


class DepthSortSystem : anax::System<anax::Requires<Movable>> {
public:
    void Update(anax::World &world) {
        auto entities = world.getEntities();

        for (auto i : entities) {
            if (i.hasComponent<Movable>()) {
                auto &textureComponent = i.getComponent<TextureComponent>();
                auto positionComponent = i.getComponent<PositionComponent>();
                auto sizeComponent = i.getComponent<SizeComponent>();
                i.getComponent<TextureComponent>().sortKey = static_cast<int>(positionComponent.SpriteTop +
                                                                              sizeComponent.SpriteHeight);
            }
        }
    }
};

#endif //ISORPG_SORT_KEY_UPDATE_H

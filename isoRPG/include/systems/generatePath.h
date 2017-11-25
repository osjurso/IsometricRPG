
#ifndef ISORPG_GENERATEPATH_H
#define ISORPG_GENERATEPATH_H


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
#include <include/components/Comp_moveble.h>
#include "pathfinding.h"


class GeneratePath
{
public:
    GeneratePath(){}

    void generate( anax::World& world, anax::Entity player)
    {
        auto enteties = world.getEntities();

        for(auto i : enteties)
        {
            PositionComponent positionComponent = i.getComponent<PositionComponent>();
            Moveble& moveble = i.getComponent<Moveble>();
            moveble.path = "";
            const int mapsize = 64;

            if(i.getComponent<Moveble>().agro)
            {
                PositionComponent playerPos = player.getComponent<PositionComponent>();

                const int distaceX = (playerPos.SpriteLeft  - positionComponent.SpriteLeft)/10;
                const int distaceY = (playerPos.SpriteTop   - positionComponent.SpriteTop)/10;

                if(0 < distaceX < mapsize && 0 < distaceY < mapsize)
                {
                    std::string path = pathFind(mapsize/2,mapsize/2,mapsize/2 + distaceX,mapsize/2 + distaceY);
                    moveble.path = path;
                }else
                {
                    moveble.agro = false;
                }
            }else
            {
                const int distaceX = (positionComponent.originPosisionX  - positionComponent.SpriteLeft)/10;
                const int distaceY = (positionComponent.originPosisionY   - positionComponent.SpriteTop)/10;

                if(0 < distaceX < mapsize && 0 < distaceY < mapsize)
                {
                    std::string path = pathFind(mapsize/2,mapsize/2,mapsize/2 + distaceX,mapsize/2 + distaceY);
                    moveble.path = path;
                }else
                {
                    i.kill();
                    world.refresh();
                }

            }

        }
    }
};

#endif //ISORPG_GENERATEPATH_H

#include <states/state_base.h>
#include <application.h>
#include <iostream>

#include <components/Comp_position.h>
#include <components/Comp_moveble.h>

#include <systems/generatePath.h>


void GeneratePath::generate(anax::World &world, anax::Entity player)
{
    auto enteties = world.getEntities();

    for(auto i : enteties)
    {
        PositionComponent positionComponent = i.getComponent<PositionComponent>();
        Movable& moveble = i.getComponent<Movable>();
        moveble.path = "";
        const int mapsize = 64;

        if(i.getComponent<Movable>().agro)
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
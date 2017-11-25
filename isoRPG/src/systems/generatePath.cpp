#include <systems/generatePath.h>


void GeneratePath::generate(anax::World &world, anax::Entity player)
{
    auto enteties = world.getEntities();

    for(auto i : enteties)
    {
        if(i.hasComponent<Movable>() && i.getId() != player.getId())
        {
            PositionComponent positionComponent = i.getComponent<PositionComponent>();
            Movable& moveble = i.getComponent<Movable>();
            moveble.path = "";
            const int mapsize = 64;

            if(i.getComponent<Movable>().agro)
            {
                PositionComponent& playerPos = player.getComponent<PositionComponent>();

                const int distaceX = (playerPos.XPos  - positionComponent.XPos)/10;
                const int distaceY = (playerPos.YPos  - positionComponent.YPos)/10;

                if(0 < distaceX < mapsize && 0 < distaceY < mapsize)
                {
                    std::string path = pathFind(mapsize/2,mapsize/2,mapsize/2 + distaceX,mapsize/2 + distaceY);
                    moveble.path = path;
                    std::cout << "Entity ID: "<< i.getId() << "  Path: " <<  path << std::endl;
                }else
                {
                    moveble.agro = false;
                    const int distaceX = (positionComponent.originPosisionX  - positionComponent.SpriteLeft)/10;
                    const int distaceY = (positionComponent.originPosisionY   - positionComponent.SpriteTop)/10;

                    if(0 < distaceX < mapsize && 0 < distaceY < mapsize)
                    {
                        std::string path = pathFind(mapsize/2,mapsize/2,mapsize/2 + distaceX,mapsize/2 + distaceY);
                        moveble.path = path;
                        std::cout << "Entity ID: "<< i.getId() << "  Path: " <<  path << std::endl;
                    }else
                    {
                        i.kill();
                        world.refresh();
                    }
                }
            }

        }
    }
}
#include <systems/generatePath.h>
#include <include/components/Comp_animation.h>


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
            moveble.curent = 0;
            const int mapsize = 64;
            int pixelsPerBlock = 10;

            if(i.getComponent<Movable>().agro)
            {
                PositionComponent& playerPos = player.getComponent<PositionComponent>();

                const int distaceX = (playerPos.XPos  - positionComponent.XPos)/10;
                const int distaceY = (playerPos.YPos  - positionComponent.YPos)/10;

                if(0 < distaceX < mapsize && 0 < distaceY < mapsize)
                {
                    std::string path = pathFind(mapsize/2,mapsize/2,mapsize/2 + distaceX,mapsize/2 + distaceY);
                    moveble.path = path;
                    for(int i = 0; i< path.length(); i++)
                    {
                        for(int n = 0; n < pixelsPerBlock ; n++)
                        {
                            char instruction = moveble.path.at(i);
                            moveble.path.push_back(instruction);
                            int index = i*pixelsPerBlock +n;
                            if(instruction == '0')
                            {
                                moveble.moveX[index] = 1;
                                moveble.moveY[index] = 0;
                            }
                            if(instruction == '1')
                            {
                                moveble.moveX[index] = 0.5;
                                moveble.moveY[index] = 0.5;
                            }
                            if(instruction == '2')
                            {
                                moveble.moveX[index] = 0;
                                moveble.moveY[index] = 1;
                            }
                            if(instruction == '3')
                            {
                                moveble.moveX[index] = -0.5;
                                moveble.moveY[index] = 0.5;
                            }
                            if(instruction == '4')
                            {
                                moveble.moveX[index] = -1;
                                moveble.moveY[index] = 0;
                            }
                            if(instruction == '5')
                            {
                                moveble.moveX[index] = -0.5;
                                moveble.moveY[index] = -0.5;
                            }
                            if(instruction == '6')
                            {
                                moveble.moveX[index] = 0;
                                moveble.moveY[index] = -1;
                            }
                            if(instruction == '7')
                            {
                                moveble.moveX[index] =0.5;
                                moveble.moveY[index] = -0.5;
                            }
                        }
                    }
                    i.getComponent<AnimationComponent>().action = "Walk";
                }else
                {
                    moveble.agro = false;
                    const int distaceX = (positionComponent.originPosisionX  - positionComponent.SpriteLeft)/10;
                    const int distaceY = (positionComponent.originPosisionY   - positionComponent.SpriteTop)/10;

                    if(0 < distaceX < mapsize && 0 < distaceY < mapsize)
                    {
                        std::string path = pathFind(mapsize/2,mapsize/2,mapsize/2 + distaceX,mapsize/2 + distaceY);
                        moveble.path = path;
                        i.getComponent<AnimationComponent>().action = "Walk";
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
void translateToArray()
{

}
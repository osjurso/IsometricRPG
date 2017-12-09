#include <systems/generatePath.h>
#include <include/components/Comp_animation.h>
#include <include/components/Comp_size.h>


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
                PositionComponent& heroPos = player.getComponent<PositionComponent>();

                auto heroSize = player.getComponent<SizeComponent>();
                auto enemySize = i.getComponent<SizeComponent>();

                // Calulation the tile position of the hero
                sf::Vector2i heroTilePos = sf::Vector2i(heroPos.XPos + heroSize.Whith/2, heroPos.SpriteTop);
                heroTilePos = sf::Vector2i((2 * heroTilePos.y + heroTilePos.x) / 64, (2 * heroTilePos.y - heroTilePos.x) / 64);

                sf::Vector2i enemyTilePos = sf::Vector2i(positionComponent.SpriteLeft + 17, positionComponent.SpriteTop + 25);
                enemyTilePos = sf::Vector2i((2 * enemyTilePos.y + enemyTilePos.x) / 64, (2 * enemyTilePos.y - enemyTilePos.x) / 64);

                if (enemyTilePos == heroTilePos)
                    continue;

                if(0 < heroTilePos.x < mapsize && 0 < heroTilePos.y < mapsize)
                {
                    std::string path = pathFind(enemyTilePos.x, enemyTilePos.y, heroTilePos.x, heroTilePos.y);

                    moveble.path = path;

                    for(int i = 0; i< path.length(); i++)
                    {
                        for(int n = 0; n < pixelsPerBlock ; n++)
                        {
                            char instruction = moveble.path.at(i);
                            moveble.path.push_back(instruction);
                            int index = i*pixelsPerBlock +n;

                            // Rotated direction clockwise because the pathfinder logic uses an orthogonal representation of the map
                            if(instruction == '7')
                            {
                                moveble.moveX[index] = 1;
                                moveble.moveY[index] = 0;
                            }
                            if(instruction == '0')
                            {
                                moveble.moveX[index] = 0.66;
                                moveble.moveY[index] = 0.33;
                            }
                            if(instruction == '1')
                            {
                                moveble.moveX[index] = 0;
                                moveble.moveY[index] = 1;
                            }
                            if(instruction == '2')
                            {
                                moveble.moveX[index] = -0.66;
                                moveble.moveY[index] = 0.33;
                            }
                            if(instruction == '3')
                            {
                                moveble.moveX[index] = -1;
                                moveble.moveY[index] = 0;
                            }
                            if(instruction == '4')
                            {
                                moveble.moveX[index] = -0.66;
                                moveble.moveY[index] = -0.33;
                            }
                            if(instruction == '5')
                            {
                                moveble.moveX[index] = 0;
                                moveble.moveY[index] = -1;
                            }
                            if(instruction == '6')
                            {
                                moveble.moveX[index] = 0.66;
                                moveble.moveY[index] = -0.33;
                            }
                        }
                    }
                    i.getComponent<AnimationComponent>().action = "Walk";
                }else
                {
                    moveble.agro = false;

                    std::string path = pathFind(enemyTilePos.x, enemyTilePos.y, heroTilePos.x, heroTilePos.y);

                    if(0 < heroTilePos.x < mapsize && 0 < heroTilePos.y < mapsize)
                    {
                        std::string path = pathFind(enemyTilePos.x, enemyTilePos.y, heroTilePos.x, heroTilePos.y);
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
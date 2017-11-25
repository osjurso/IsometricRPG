
#ifndef ISORPG_COLLSION_H
#define ISORPG_COLLSION_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>


#include <include/components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <include/components/Comp_moveble.h>
#include <iostream>

class Collision : anax::System<anax::Requires<PositionComponent, SizeComponent>>
{
public:
Collision(){}

void checkCollision(anax::World& world)
{
    auto enteties = world.getEntities();

    for(auto i : enteties)
    {
        for(auto e : enteties)
        {
            if(e.getId() != i.getId())
            {
                if(i.hasComponent<Movable>())
                {
                    PositionComponent& entity1Pos = i.getComponent<PositionComponent>();
                    PositionComponent& entity2Pos = e.getComponent<PositionComponent>();
                    SizeComponent& entity1Size = i.getComponent<SizeComponent>();
                    SizeComponent& entity2Size = e.getComponent<SizeComponent>();

                    bool Left = false;
                    bool Right = false;
                    bool Top = false;
                    bool Bottom = false;


                    if(entity1Pos.XPos + entity1Size.Width >= entity2Pos.XPos &&
                       entity1Pos.XPos + entity1Size.Width <= entity2Pos.XPos + entity2Size.Width)
                    {
                        //Right side of entity1 inside entity2
                        Right = true;
                    }
                    if(entity1Pos.XPos >= entity2Pos.XPos &&
                       entity1Pos.XPos <= entity2Pos.XPos + entity2Size.Width)
                    {
                        //Left side of entity1 inside entity2
                        Left = true;
                    }
                    if(entity1Pos.YPos+ entity1Size.Height <= entity2Pos.YPos &&
                       entity1Pos.YPos+ entity1Size.Height >= entity2Pos.YPos + entity2Size.Height)
                    {
                        //Bottem of entity1 inside entity2
                        Bottom = true;
                    }
                    if(entity1Pos.YPos >= entity2Pos.YPos &&
                       entity1Pos.YPos <= entity2Pos.YPos + entity2Size.Height)
                    {
                        //Top of entity inside entity2
                        Top = true;
                    }

                    if(Bottom &&(Left || Right))
                    {
                        std::cout << "Kolision to the Bottom" << std::endl;
                    }
                    if(Top &&(Left || Right))
                    {
                        std::cout << "Kolision to the Top" << std::endl;
                    }
                    if(Left &&(Bottom || Top))
                    {
                        std::cout << "Kolision to the Left" << std::endl;
                    }
                    if(Right &&(Bottom || Top))
                    {
                        std::cout << "Kolision to the Right" << std::endl;
                    }
                }
            }
        }
    }
}
};


#endif //ISORPG_COLLSION_H

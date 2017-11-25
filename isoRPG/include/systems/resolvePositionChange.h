
#ifndef ISORPG_RESOLVEPOSITIONCHANGE_H
#define ISORPG_RESOLVEPOSITIONCHANGE_H

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
#include <include/components/Comp_talk.h>
#include <fstream>
#include <include/components/Comp_moveble.h>
#include <include/components/Comp_animation.h>


class PostitonChange
{
public:
    PostitonChange(){}

    void change(anax::World& world)
    {
        auto enteties = world.getEntities();

        for(auto i : enteties)
        {
            if(i.hasComponent<Moveble>())
            {
                if(i.getComponent<Moveble>().path != "")
                {
                    moveCreature(i);
                }else
                {
                    i.getComponent<Moveble>().agro = false;
                }
            }
        }
    }
private:
    void moveCreature(anax::Entity& entity)
    {
        Moveble& moveble = entity.getComponent<Moveble>();
        PositionComponent& positionComponent = entity.getComponent<PositionComponent>();
        AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();
        int speed = 10;
        if(moveble.path.at(0) == '0')
        {
            //Move East
            animationComponent.direction = "Right";
            positionComponent.XPos += speed;
            positionComponent.SpriteLeft += speed;

        }else if(moveble.path.at(0) == '1')
        {
            //Move South East
            positionComponent.YPos += speed/2;
            positionComponent.SpriteTop += speed/2;
            positionComponent.XPos += speed/2;
            positionComponent.SpriteLeft += speed/2;

        }else if(moveble.path.at(0) == '2')
        {
            //Move South
            animationComponent.direction = "Down";
            positionComponent.YPos += speed;
            positionComponent.SpriteTop += speed;

        }else if(moveble.path.at(0) == '3')
        {
            //Move South West
            positionComponent.YPos += speed/2;
            positionComponent.SpriteTop += speed/2;
            positionComponent.XPos -= speed/2;
            positionComponent.SpriteLeft -= speed/2;
        }else if(moveble.path.at(0) == '4')
        {
            //Move West
            animationComponent.direction = "Left";
            positionComponent.XPos -= speed;
            positionComponent.SpriteLeft -= speed;

        }
        else if(moveble.path.at(0) == '5')
        {
            //Move North West
            positionComponent.YPos -= speed/2;
            positionComponent.SpriteTop -= speed/2;
            positionComponent.XPos -= speed/2;
            positionComponent.SpriteLeft -= speed/2;

        }else if(moveble.path.at(0) == '6')
        {
            //Move North
            animationComponent.direction = "Up";
            positionComponent.YPos -= speed;
            positionComponent.SpriteTop -= speed;

        }else if(moveble.path.at(0) == '7')
        {
            //Move South West
            positionComponent.YPos -= speed/2;
            positionComponent.SpriteTop -= speed/2;
            positionComponent.XPos += speed/2;
            positionComponent.SpriteLeft += speed/2;
        }


        moveble.path.erase(0,1);
        std::cout << moveble.path << std::endl;
    }

};


#endif //ISORPG_RESOLVEPOSITIONCHANGE_H

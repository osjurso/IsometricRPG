
#ifndef ISORPG_MOVECREATURES_H
#define ISORPG_MOVECREATURES_H


#include <anax/System.hpp>
#include <states/state_base.h>


#include <include/components/Comp_size.h>
#include <include/components/Comp_mousedOver.h>
#include <components/Comp_position.h>
#include <iostream>
#include <include/components/Comp_looteble.h>
#include <include/components/Comp_talk.h>
#include <include/components/Comp_moveble.h>
#include "loot.h"
#include "talk.h"

struct MoveCreature : anax::System<anax::Requires<Movable>>
{
public:
    MoveCreature()
    {}
    void Move(anax::World& world, int GoalX, int GoalY)
    {
        auto enteties = world.getEntities();
        for(auto i : enteties)
        {
            if(i.hasComponent<Movable>())
                process(i, GoalX, GoalY);
        }
    }


private:
    void process(anax::Entity entity, int GoalX, int GoalY)
    {
        PositionComponent positionComponent = entity.getComponent<PositionComponent>();
        //std::string path= pathFind(positionComponent.XPos,positionComponent.XPos,GoalX,GoalY);
        //if(path=="") std::cout<<"An empty route generated!"<<std::endl;
        //std::cout << path << std::endl;

    }
};

#endif //ISORPG_MOVECREATURES_H

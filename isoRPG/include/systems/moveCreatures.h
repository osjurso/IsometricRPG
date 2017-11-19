
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
#include "include/systems/pathfinding.h"

struct MoveCreature : anax::System<anax::Requires<Moveble>>
{
public:
    MoveCreature()
    {}
    void Move(anax::World& world, int GoalX, int GoalY, int mapX, int mapY)
    {
        auto enteties = world.getEntities();
        for(auto i : enteties)
        {
            if(i.hasComponent<Moveble>())
                process(i, GoalX, GoalY, mapX, mapY);
        }
    }


private:
    void process(anax::Entity entity, int GoalX, int GoalY, int mapX, int mapY )
    {
        PositionComponent positionComponent = entity.getComponent<PositionComponent>();
        PathFiding pathFiding(mapX,mapY);
        std::string path = pathFiding.findPath(positionComponent.SpriteLeft,positionComponent.SpriteTop,GoalX,GoalY);
    }
};

#endif //ISORPG_MOVECREATURES_H

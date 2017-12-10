#ifndef ISORPG_COLLISIONSYSTEM_H
#define ISORPG_COLLISIONSYSTEM_H


#include <anax/Entity.hpp>
#include "include/components/comp_collision.h"
#include "include/components/Comp_position.h"


struct CollisionSystem : anax::System<anax::Requires<PositionComponent, CollisionComponent>>
{
public:
    void update(float dt, anax::World& world);

    void onCollisionOccured(anax::Entity& e1, anax::Entity& e2);
};


#endif //ISORPG_COLLISIONSYSTEM_H

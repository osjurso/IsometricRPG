#ifndef ISORPG_COMP_COLLISION_H
#define ISORPG_COMP_COLLISION_H

#include <anax/Component.hpp>

#include <SFML/Graphics/Rect.hpp>

struct CollisionComponent : anax::Component
{
    // Bounding box rectangle for collision
    sf::FloatRect boundingBox;

    //Flag to determine whether this object causes events or not
    bool causesEvents;
};

#endif //ISORPG_COMP_COLLISION_H

#include <SFML/Graphics/Transformable.hpp>
#include <components/comp_collision.h>
#include <components/Comp_Texture.h>
#include <components/Comp_position.h>
#include <iostream>
#include "systems/collision_system.h"

enum Direction
{
    East = 0,
    SouthEast = 1,
    South = 2,
    SoutWest = 3,
    West = 4,
    NorthWest = 5,
    North = 6,
    NorthEast = 7,
};

static sf::FloatRect getBBoxRectFor(const sf::Vector2f& v, const sf::FloatRect& bbox)
{
    // The collision component only contains positions relative to (0,0) in the texture
    return sf::FloatRect(v.x + bbox.left, v.y + bbox.top, bbox.width, bbox.height);
}

static sf::FloatRect getBBoxRectFor(const anax::Entity& entity)
{
    auto& positionComponent = entity.getComponent<PositionComponent>();
    sf::Vector2f v(positionComponent.SpriteLeft, positionComponent.SpriteTop);

    auto& bbox = entity.getComponent<CollisionComponent>().boundingBox;
    return getBBoxRectFor(v, bbox);
}

void CollisionSystem::update(float dt, anax::World& world)
{
    auto entities = world.getEntities();

    sf::FloatRect rect1;
    sf::FloatRect rect2;

    for (std::size_t i = 0; i < entities.size(); ++i)
    {
        auto& e1 = entities[i];

        if (!e1.hasComponent<CollisionComponent>() || !e1.getComponent<CollisionComponent>().causesEvents)
            continue;

        rect1 = getBBoxRectFor(e1);

        for (std::size_t j = i+1; j < entities.size(); ++j)
        {
            auto& e2 = entities[j];

            if (!e2.hasComponent<CollisionComponent>())
                continue;

            rect2 = getBBoxRectFor(e2);

            if(rect1.intersects(rect2))
            {
                onCollisionOccurred(e1, e2);
            }
        }
    }
}


void CollisionSystem::onCollisionOccurred(anax::Entity &e1, anax::Entity &e2)
{
    auto& e1CollisionComp = e1.getComponent<CollisionComponent>();
    auto& e2CollisionComp = e2.getComponent<CollisionComponent>();

    if (e1CollisionComp.causesEvents && e2CollisionComp.causesEvents)
    {
        //std::cout << "Collision between entities" << std::endl;
    }
    else
    {
        std::cout << "Collision between player and Object" << std::endl;
    }
}
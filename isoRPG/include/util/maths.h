#ifndef ISORPG_MATHS_H
#define ISORPG_MATHS_H

#include <SFML/Graphics.hpp>

/*
 * Overloaded function to convert a world position to a screen (view) position
 * CartX = (2 * isoY + isoX) / 2
 * cartY = (2 * isoY - isoX) / 2
 */

sf::Vector2f IsometricToCartesian(sf::Vector2f v)
{
    return sf::Vector2f((2 * v.y + v.x) / 2, (2 * v.y - v.x) / 2);
}

sf::Vector2i IsometricToCartesian(sf::Vector2i v)
{
    return sf::Vector2i((2 * v.y + v.x) / 2, (2 * v.y - v.x) / 2);
}


/*
 * Overloaded function to convert a screen (view) position to a world position
 * isoX = cartX - cartY
 * isoY = (cartX + CartY) / 2
 */
sf::Vector2f CartesianToIsometric(sf::Vector2f v)
{
    return sf::Vector2f((v.x - v.y), (v.x + v.y)/2);
}

sf::Vector2i CartesianToIsometric(sf::Vector2i v)
{
    return sf::Vector2i((v.x - v.y), (v.x + v.y)/2);
}

#endif //ISORPG_MATHS_H

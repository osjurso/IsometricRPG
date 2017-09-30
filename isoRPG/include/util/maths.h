#ifndef ISORPG_MATHS_H
#define ISORPG_MATHS_H

#include <SFML/Graphics.hpp>

// Function to convert a world position to a screen (view) position
// ScreenX = 2*WorldX - 2*WorldY
// ScreenY = WorldX + WorldY
sf::Vector2f WorldToScreen(sf::Vector2f v)
{
    return sf::Vector2f(2.0f*v.x - 2.0f*v.y, v.x + v.y);
}

// Function to convert a screen (view) position to a world position
// WorldX = (ScreenX + 2*ScreenY)/4
// WorldY = (2*ScreenY - ScreenX)/4
sf::Vector2f ScreenToWorld(sf::Vector2f v)
{
    return sf::Vector2f((v.x + 2.0f * v.y) / 4.0f, (2.0f * v.y - v.x) / 4.0f);
}

#endif //ISORPG_MATHS_H

#ifndef ISORPG_COMP_ANIMATION_H
#define ISORPG_COMP_ANIMATION_H

#include "states/state_base.h"

class AnimationComponent: public anax::Component
{
public:
    sf::Vector2u imageCounter;
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;
    float deltaTime;
    bool idle = true;
    bool changedDirection = false;
    int pixels;
    std::string direction;
    unsigned int row;
    sf::Vector2f movementDirection;
    int movementSpeed;
    sf::Clock animationClock;
    sf::Clock idleTimer;

    int idleStart = 0;
    int idleEnd = 3;
    int walkStart = 4;
    int walkEnd = 11;
    int attackStart = 12;
    int attackEnd = 15;
    int defendStart = 16;
    int defendEnd = 17;

    int rowWest = 0;
    int rowNorthWest = 1;
    int rowNorth = 2;
    int rowNorthEast = 3;
    int rowEast = 4;
    int rowSouthEast = 5;
    int rowSouth = 6;
    int rowSouthWest = 7;
};

#endif //ISORPG_COMP_ANIMATION_H

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

};

#endif //ISORPG_COMP_ANIMATION_H

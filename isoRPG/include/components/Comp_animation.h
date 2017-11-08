#ifndef ISORPG_COMP_ANIMATION_H
#define ISORPG_COMP_ANIMATION_H

#include "states/state_base.h"

class AnimationComponent: public anax::Component
{
    sf::Vector2u imageCounter;
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;
};

#endif //ISORPG_COMP_ANIMATION_H

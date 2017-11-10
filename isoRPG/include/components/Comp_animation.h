#ifndef ISORPG_COMP_ANIMATION_H
#define ISORPG_COMP_ANIMATION_H

#include "states/state_base.h"

class AnimationComponent: public anax::Component
{

public:
    AnimationComponent(sf::Vector2u imageCount, float switchTime);
    ~AnimationComponent();

    void walk(int row, float deltaTime, bool faceRight, bool faceUp, sf::Vector2f speed);

public:
    sf::IntRect spriteRect;

private:
    sf::Vector2u imageCounter;
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;
    int pixleWidth = 128;
    int pixleHeight = 128;

    bool idle = true;

};

#endif //ISORPG_COMP_ANIMATION_H

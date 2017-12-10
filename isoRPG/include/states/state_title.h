#ifndef ISORPG_STATE_TITLE_H
#define ISORPG_STATE_TITLE_H

#include <SFML/Graphics.hpp>

#include "state_base.h"

class StateTitle : public StateBase
{
public:
    StateTitle(StateStack& stack, Context context);
    ~StateTitle();

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event& event) override;


private:
    struct KeyFrame
    {
        sf::Time time;
        sf::Vector2f position;
        float scale { 1.f };
    };
    struct Animation
    {
        KeyFrame start;
        KeyFrame end;
    };


private:
    sf::Sprite logoSprite, isoSprite, rpgSprite;

    float shakeStrength;
    float letterScale;
    sf::Time shakeLength;
    sf::Time fadeStart;
    sf::Time length;
    sf::Time splashStart;

    const sf::Vector2f screenSize;
    const sf::View startingView;
    const sf::Time shakeStart;
    sf::Clock clock;
    sf::Time currentTime;
    sf::View view;

    Animation animationLogo;
    Animation animationIso;
    Animation animationRpg;

    void prepareAnimations();
    void updateObjects(sf::Sprite &sprite, const Animation &animation);
    void updateFade();
    void updateShake(const sf::View &startingView);
};

#endif //ISORPG_STATE_TITLE_H

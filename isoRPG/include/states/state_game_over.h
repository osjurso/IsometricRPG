#ifndef ISORPG_STATE_GAME_OVER_H
#define ISORPG_STATE_GAME_OVER_H


#include <include/gameEngine/state_stack.h>

class StateGameOver : public StateBase
{
public:
    StateGameOver(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event &event) override;


private:
    sf::Text mTitleText;
    sf::Text mRespawnText;
    sf::RectangleShape backgroundShape;

    std::vector<sf::Text> mOptions;
    std::size_t mOptionIndex;

    sf::Clock clock;
    sf::Time currentTime;
    sf::Time titleFadeInStart;
    sf::Time titleFadeInLength;
    sf::Time titleFadeOutStart;
    sf::Time titleFadeOutLength;
    sf::Time fadeOutStart;
    sf::Time fadeOutLength;

    bool respawn;
};


#endif //ISORPG_STATE_GAME_OVER_H

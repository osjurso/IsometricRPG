#ifndef ISORPG_STATE_GAME_H
#define ISORPG_STATE_GAME_H

#include <SFML/Graphics/Sprite.hpp>

#include "state_base.h"

class StateMenu : public StateBase
{
public:
    StateMenu(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event& event) override;

    void updateOptionText();


private:
    enum OptionNames
    {
        Play,
        Settings,
        About,
        Exit,
    };


private:
    sf::Sprite mLogoSprite;
    sf::Sprite mBackdrop;
    sf::Sprite mFire;
    sf::IntRect spriteRect;
    sf::Clock clock;

    std::vector<sf::Text> mOptions;
    std::size_t mOptionIndex;
};

#endif //ISORPG_STATE_GAME_H

#ifndef ISORPG_PAUSE_STATE_H
#define ISORPG_PAUSE_STATE_H

#include "state_base.h"

class StatePause : public StateBase
{
public:
    StatePause(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event &event) override;

    void updateOptionText();

private:
    enum OptionNames
    {
        resume,
        settings,
        Save,
        exit,
    };


private:
    sf::Text mPauseText;

    std::vector<sf::Text> mOptions;
    std::size_t mOptionIndex;

};


#endif //ISORPG_PAUSE_STATE_H

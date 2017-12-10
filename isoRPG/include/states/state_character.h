#ifndef ISORPG_STATE_CHARACTER_H
#define ISORPG_STATE_CHARACTER_H


#include "state_base.h"

class StateCharacter : public StateBase
{
public:
    StateCharacter(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event &event) override;

private:
    bool firstFull;
    bool secondFull;
    bool thirdFull;


};


#endif //ISORPG_STATE_CHARACTER_H

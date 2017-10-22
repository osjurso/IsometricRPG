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
    sf::Sprite mBackdrop;

    sf::Sprite mCharacterBox1;
    sf::Sprite mCharacterBox2;
    sf::Sprite mCharacterBox3;

    sf::Text mCharacterClass1;
    sf::Text mCharacterName1;

    sf::Text mCharacterClass2;
    sf::Text mCharacterName2;

    sf::Text mCharacterClass3;
    sf::Text mCharacterName3;



};


#endif //ISORPG_STATE_CHARACTER_H

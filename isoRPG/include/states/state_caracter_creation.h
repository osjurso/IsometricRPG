#ifndef ISORPG_STATE_CARACTER_CREATION_H
#define ISORPG_STATE_CARACTER_CREATION_H

#include "state_base.h"

class StateCaracterCreation : public StateBase
{
public:
    StateCaracterCreation(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event &event) override;

private:
    int saveNr = -1;
    std::string saveFile;
    std::string caracterNameText;
    anax::Entity CaracterName;
    bool typing = true;

};


#endif //ISORPG_STATE_CARACTER_CREATION_H

#ifndef ISORPG_STATE_SETTINGS_H
#define ISORPG_STATE_SETTINGS_H

#include "state_base.h"

class StateSettings : public StateBase
{
public:
    StateSettings(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event &event) override;

private:
    sf::Text mTempText;
    sf::Sprite mBackdrop;

    int VolumeX;

    sf::Sprite masterVolume;
    sf::Sprite musicVolume;
    sf::Sprite SFXVolume;

    sf::Sprite VolumeKnobMaster;
    sf::Sprite VolumeKnobMusic;
    sf::Sprite VolumeKnobSFX;
};


#endif //ISORPG_STATE_SETTINGS_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "include/states/state_settings.h"
#include "include/gameEngine/resource_holder.h"

StateSettings::StateSettings(StateStack &stack, StateBase::Context context)
        : StateBase(stack, context)
{
    sf::Font& font = context.fonts->get(Fonts::Main);

    mTempText.setFont(context.fonts->get(Fonts::Main));
    mTempText.setString("Do something here");

    mBackdrop.setTexture(context.textures->get(Textures::SettingsBackdorp));
    mBackdrop.setPosition(0,0);

    masterVolume.setTexture(context.textures->get(Textures::SettingsSlider));
    SFXVolume.setTexture(context.textures->get(Textures::SettingsSlider));
    musicVolume.setTexture(context.textures->get(Textures::SettingsSlider));

    VolumeKnobMaster.setTexture(context.textures->get(Textures::SettingKnob));
    VolumeKnobSFX.setTexture(context.textures->get(Textures::SettingKnob));
    VolumeKnobMusic.setTexture(context.textures->get(Textures::SettingKnob));

    VolumeX = 800;
    int SliderSpace = 100;

    masterVolume.setPosition(VolumeX,2*SliderSpace);
    SFXVolume.setPosition(VolumeX,3*SliderSpace);
    musicVolume.setPosition(VolumeX,4*SliderSpace);

    VolumeKnobMaster.setPosition(VolumeX+ SFXVolume.getGlobalBounds().width/2,2*SliderSpace-15);
    VolumeKnobMusic.setPosition(VolumeX+ SFXVolume.getGlobalBounds().width/2,3*SliderSpace-15);
    VolumeKnobSFX.setPosition(VolumeX + SFXVolume.getGlobalBounds().width/2,4*SliderSpace-15);

}


void StateSettings::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.draw(mTempText);
    window.draw(mBackdrop);


    window.draw(masterVolume);
    window.draw(SFXVolume);
    window.draw(musicVolume);

    window.draw(VolumeKnobSFX);
    window.draw(VolumeKnobMusic);
    window.draw(VolumeKnobMaster);
}

bool StateSettings::update(sf::Time dt)
{
    return true;
}

bool StateSettings::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Menu);
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {

    }

    return true;
}



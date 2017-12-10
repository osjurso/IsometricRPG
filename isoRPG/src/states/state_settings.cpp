#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <include/collections/drawable.h>
#include <include/systems/drawEntety.h>

#include "include/states/state_settings.h"
#include "include/gameEngine/resource_holder.h"

StateSettings::StateSettings(StateStack &stack, StateBase::Context context)
        : StateBase(stack, context)
{
    sf::Font& font = context.fonts->get(Fonts::RPG);
    anax::World& world = *getContext().world;

    anax::Entity background = world.createEntity();

    anax::Entity masterSlider = world.createEntity();
    anax::Entity musicSlider = world.createEntity();
    anax::Entity sfxSlider = world.createEntity();

    anax::Entity masterKnob = world.createEntity();
    anax::Entity musicKnob = world.createEntity();
    anax::Entity sfxKnob = world.createEntity();

    Draweble draweble;
    int volumeX = 800;
    int volumeY = 200;
    int SliderSpace = 100;
    draweble.makeDraweble(getContext().textures->get(Textures::SettingsBackdorp),0,0,background ,"Settings");

    draweble.makeDraweble(getContext().textures->get(Textures::SettingsSlider),volumeX, volumeY                , masterSlider,"Settings");
    draweble.makeDraweble(getContext().textures->get(Textures::SettingsSlider),volumeX, volumeY + SliderSpace  , musicSlider ,"Settings");
    draweble.makeDraweble(getContext().textures->get(Textures::SettingsSlider),volumeX, volumeY + SliderSpace*2, sfxSlider   ,"Settings");

    draweble.makeDraweble(getContext().textures->get(Textures::SettingKnob),volumeX, volumeY                 -12, masterKnob,"Settings");
    draweble.makeDraweble(getContext().textures->get(Textures::SettingKnob),volumeX, volumeY + SliderSpace   -12, musicKnob ,"Settings");
    draweble.makeDraweble(getContext().textures->get(Textures::SettingKnob),volumeX, volumeY + SliderSpace*2 -12, sfxKnob   ,"Settings");

}


void StateSettings::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());


    anax::World& world = *getContext().world;
    DrawEntetys drawEntetys;
    drawEntetys.draw(window,world,"Settings");

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



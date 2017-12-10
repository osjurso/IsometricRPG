#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <include/collections/drawable.h>
#include <include/systems/drawEntety.h>
#include <include/components/Comp_Changeble.h>
#include <include/collections/drawebleText.h>

#include "include/states/state_settings.h"
#include "include/gameEngine/resource_holder.h"

StateSettings::StateSettings(StateStack &stack, StateBase::Context context)
        : StateBase(stack, context)
{
    sf::Font& font = context.fonts->get(Fonts::RPG);
    anax::World& world = *getContext().world;
    sf::RenderWindow& window = *getContext().window;

    anax::Entity background = world.createEntity();

    anax::Entity masterSlider = world.createEntity();
    anax::Entity musicSlider = world.createEntity();
    anax::Entity sfxSlider = world.createEntity();

    anax::Entity masterKnob = world.createEntity();
    anax::Entity musicKnob = world.createEntity();
    anax::Entity sfxKnob = world.createEntity();

    masterKnob.addComponent<ChangebleComponent>();
    musicKnob.addComponent<ChangebleComponent>();
    sfxKnob.addComponent<ChangebleComponent>();

    Draweble draweble;
    int volumeX = 800;
    int volumeY = 200;
    int SliderSpace = 100;
    draweble.makeDraweble(getContext().textures->get(Textures::SettingsBackdorp),0,0,background ,"Settings");

    draweble.makeDraweble(getContext().textures->get(Textures::SettingsSlider),volumeX, volumeY                , masterSlider,"Settings");
    draweble.makeDraweble(getContext().textures->get(Textures::SettingsSlider),volumeX, volumeY + SliderSpace  , musicSlider ,"Settings");
    draweble.makeDraweble(getContext().textures->get(Textures::SettingsSlider),volumeX, volumeY + SliderSpace*2, sfxSlider   ,"Settings");

    draweble.makeDraweble(getContext().textures->get(Textures::SettingKnob),volumeX+ masterSlider.getComponent<TextureComponent>().sprite[0].getLocalBounds().width/2, volumeY                 -12, masterKnob,"Settings");
    draweble.makeDraweble(getContext().textures->get(Textures::SettingKnob),volumeX+ masterSlider.getComponent<TextureComponent>().sprite[0].getLocalBounds().width/2, volumeY + SliderSpace   -12, musicKnob ,"Settings");
    draweble.makeDraweble(getContext().textures->get(Textures::SettingKnob),volumeX + masterSlider.getComponent<TextureComponent>().sprite[0].getLocalBounds().width/2, volumeY + SliderSpace*2 -12, sfxKnob   ,"Settings");

    masterKnob.getComponent<ChangebleComponent>().min = volumeX;
    masterKnob.getComponent<ChangebleComponent>().max = volumeX + masterSlider.getComponent<TextureComponent>().sprite[0].getLocalBounds().width - 20;
    masterKnob.getComponent<ChangebleComponent>().source = "Master";
    musicKnob.getComponent<ChangebleComponent>().min = volumeX;
    musicKnob.getComponent<ChangebleComponent>().max = volumeX + musicSlider.getComponent<TextureComponent>().sprite[0].getLocalBounds().width - 20;
    musicKnob.getComponent<ChangebleComponent>().source = "Music";
    sfxKnob.getComponent<ChangebleComponent>().min = volumeX;
    sfxKnob.getComponent<ChangebleComponent>().max = volumeX + sfxSlider.getComponent<TextureComponent>().sprite[0].getLocalBounds().width- 20;
    sfxKnob.getComponent<ChangebleComponent>().source = "SFX";


    anax::Entity masterText = world.createEntity();
    anax::Entity musicText = world.createEntity();
    anax::Entity sfxText = world.createEntity();

    sf::View cam = window.getView();
    DrawebleText drawebleText;
    drawebleText.setUpDrawebleText(masterText,"Master",cam,"Settings",1,font,sf::Color().Black);
    drawebleText.setUpDrawebleText(musicText,"Music",cam,"Settings",1,font,sf::Color().Black);
    drawebleText.setUpDrawebleText(sfxText,"SFX",cam,"Settings",1,font,sf::Color().Black);

    masterText.getComponent<PositionComponent>().XPos = volumeX;
    masterText.getComponent<PositionComponent>().YPos = volumeY -50;

    musicText.getComponent<PositionComponent>().XPos = volumeX;
    musicText.getComponent<PositionComponent>().YPos = volumeY -50 +SliderSpace;

    sfxText.getComponent<PositionComponent>().XPos = volumeX;
    sfxText.getComponent<PositionComponent>().YPos = volumeY-50 +SliderSpace*2;
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
    sf::RenderWindow& window = *getContext().window;
    auto entitys = getContext().world->getEntities();
    for(auto i: entitys)
    {
        if(i.hasComponent<ChangebleComponent>())
        {
            if(i.getComponent<ChangebleComponent>().changeble)
            {

                if(i.getComponent<ChangebleComponent>().min < sf::Mouse::getPosition(window).x && sf::Mouse::getPosition(window).x < i.getComponent<ChangebleComponent>().max)
                {
                    i.getComponent<PositionComponent>().XPos = sf::Mouse::getPosition(window).x;
                }
                if(i.getComponent<ChangebleComponent>().source == "Master")
                {
                    masterVolume = (i.getComponent<ChangebleComponent>().max - i.getComponent<ChangebleComponent>().min) /( sf::Mouse::getPosition(window).x - i.getComponent<ChangebleComponent>().min);
                    getContext().music->setVolume(100*masterVolume*musicVolume);
                    getContext().sounds->setVolume(100*masterVolume*SFXVolume);
                }
                if(i.getComponent<ChangebleComponent>().source == "Music")
                {
                    musicVolume = (i.getComponent<ChangebleComponent>().max - i.getComponent<ChangebleComponent>().min) /( sf::Mouse::getPosition(window).x - i.getComponent<ChangebleComponent>().min);
                    getContext().music->setVolume(100*masterVolume*musicVolume);
                }
                if(i.getComponent<ChangebleComponent>().source == "SFX")
                {
                    SFXVolume = (i.getComponent<ChangebleComponent>().max - i.getComponent<ChangebleComponent>().min) /( sf::Mouse::getPosition(window).x - i.getComponent<ChangebleComponent>().min);
                    getContext().sounds->setVolume(100*masterVolume*SFXVolume);
                }

            }
        }
    }
    return true;
}

bool StateSettings::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        auto entitys = getContext().world->getEntities();
        anax::World& world = *getContext().world;
        for(auto i : entitys)
        {
            i.kill();
            world.refresh();
        }
        requestStackPop();
        requestStackPush(States::Menu);
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::RenderWindow& window = *getContext().window;
        auto entitys = getContext().world->getEntities();
        for(auto i: entitys)
        {
            if(i.hasComponent<ChangebleComponent>())
            {
                sf::IntRect entityRect;
                PositionComponent& positionComponent = i.getComponent<PositionComponent>();
                SizeComponent& sizeComponent = i.getComponent<SizeComponent>();
                entityRect.top =  positionComponent.YPos;
                entityRect.left = positionComponent.XPos;
                entityRect.width =  sizeComponent.Whith;
                entityRect.height = sizeComponent.Height;
                if(entityRect.contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                {
                    i.getComponent<ChangebleComponent>().changeble = true;
                }
                else
                {
                    i.getComponent<ChangebleComponent>().changeble = false;
                }
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        sf::RenderWindow &window = *getContext().window;
        auto entitys = getContext().world->getEntities();
        for (auto i: entitys)
        {
            if (i.hasComponent<ChangebleComponent>())
            {
                i.getComponent<ChangebleComponent>().changeble = false;
            }
        }
    }

    return true;
}



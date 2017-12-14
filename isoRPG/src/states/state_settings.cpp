#include <SFML/Graphics/RenderWindow.hpp>
#include <collections/drawable.h>
#include <systems/drawEntety.h>
#include <components/Comp_Changeable.h>
#include <collections/drawableText.h>

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

    masterKnob.addComponent<ChangeableComponent>();
    musicKnob.addComponent<ChangeableComponent>();
    sfxKnob.addComponent<ChangeableComponent>();

    Drawable draweble;
    int volumeX = 800;
    int volumeY = 200;
    int SliderSpace = 100;
    draweble.makeDrawable(getContext().textures->get(Textures::SettingsBackdorp), 0, 0, background, "Settings");

    draweble.makeDrawable(getContext().textures->get(Textures::SettingsSlider), volumeX, volumeY, masterSlider,
                          "Settings");
    draweble.makeDrawable(getContext().textures->get(Textures::SettingsSlider), volumeX, volumeY + SliderSpace,
                          musicSlider, "Settings");
    draweble.makeDrawable(getContext().textures->get(Textures::SettingsSlider), volumeX, volumeY + SliderSpace * 2,
                          sfxSlider, "Settings");

    draweble.makeDrawable(getContext().textures->get(Textures::SettingKnob),
                          volumeX + masterSlider.getComponent<TextureComponent>().sprite[0].getLocalBounds().width / 2,
                          volumeY - 12, masterKnob, "Settings");
    draweble.makeDrawable(getContext().textures->get(Textures::SettingKnob),
                          volumeX + masterSlider.getComponent<TextureComponent>().sprite[0].getLocalBounds().width / 2,
                          volumeY + SliderSpace - 12, musicKnob, "Settings");
    draweble.makeDrawable(getContext().textures->get(Textures::SettingKnob),
                          volumeX + masterSlider.getComponent<TextureComponent>().sprite[0].getLocalBounds().width / 2,
                          volumeY + SliderSpace * 2 - 12, sfxKnob, "Settings");

    masterKnob.getComponent<ChangeableComponent>().min = volumeX;
    masterKnob.getComponent<ChangeableComponent>().max = volumeX + masterSlider.getComponent<TextureComponent>().sprite[0].getLocalBounds().width - 20;
    masterKnob.getComponent<ChangeableComponent>().source = "Master";
    musicKnob.getComponent<ChangeableComponent>().min = volumeX;
    musicKnob.getComponent<ChangeableComponent>().max = volumeX + musicSlider.getComponent<TextureComponent>().sprite[0].getLocalBounds().width - 20;
    musicKnob.getComponent<ChangeableComponent>().source = "Music";
    sfxKnob.getComponent<ChangeableComponent>().min = volumeX;
    sfxKnob.getComponent<ChangeableComponent>().max = volumeX + sfxSlider.getComponent<TextureComponent>().sprite[0].getLocalBounds().width- 20;
    sfxKnob.getComponent<ChangeableComponent>().source = "SFX";


    anax::Entity masterText = world.createEntity();
    anax::Entity musicText = world.createEntity();
    anax::Entity sfxText = world.createEntity();

    sf::View cam = window.getView();
    DrawableText drawebleText;
    drawebleText.setUpDrawableText(masterText, "Master", cam, "Settings", 1, font, sf::Color().Black);
    drawebleText.setUpDrawableText(musicText, "Music", cam, "Settings", 1, font, sf::Color().Black);
    drawebleText.setUpDrawableText(sfxText, "SFX", cam, "Settings", 1, font, sf::Color().Black);

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
    window.clear();

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
        if(i.hasComponent<ChangeableComponent>())
        {
            if(i.getComponent<ChangeableComponent>().changeble)
            {

                if(i.getComponent<ChangeableComponent>().min < sf::Mouse::getPosition(window).x && sf::Mouse::getPosition(window).x < i.getComponent<ChangeableComponent>().max)
                {
                    i.getComponent<PositionComponent>().XPos = sf::Mouse::getPosition(window).x;
                }
                if(i.getComponent<ChangeableComponent>().source == "Master")
                {
                    masterVolume = (i.getComponent<ChangeableComponent>().max - i.getComponent<ChangeableComponent>().min) /( sf::Mouse::getPosition(window).x - i.getComponent<ChangeableComponent>().min);
                    getContext().music->setVolume(100*masterVolume*musicVolume);
                    getContext().sounds->setVolume(100*masterVolume*SFXVolume);
                }
                if(i.getComponent<ChangeableComponent>().source == "Music")
                {
                    musicVolume = (i.getComponent<ChangeableComponent>().max - i.getComponent<ChangeableComponent>().min) /( sf::Mouse::getPosition(window).x - i.getComponent<ChangeableComponent>().min);
                    getContext().music->setVolume(100*masterVolume*musicVolume);
                }
                if(i.getComponent<ChangeableComponent>().source == "SFX")
                {
                    SFXVolume = (i.getComponent<ChangeableComponent>().max - i.getComponent<ChangeableComponent>().min) /( sf::Mouse::getPosition(window).x - i.getComponent<ChangeableComponent>().min);
                    getContext().sounds->setVolume(100*masterVolume*SFXVolume);
                }

            }
        }
    }

    return false;
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
        requestStateChange(States::Menu);
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::RenderWindow& window = *getContext().window;
        auto entitys = getContext().world->getEntities();
        for(auto i: entitys)
        {
            if(i.hasComponent<ChangeableComponent>())
            {
                sf::IntRect entityRect;
                PositionComponent& positionComponent = i.getComponent<PositionComponent>();
                SizeComponent& sizeComponent = i.getComponent<SizeComponent>();
                entityRect.top =  positionComponent.YPos;
                entityRect.left = positionComponent.XPos;
                entityRect.width =  sizeComponent.width;
                entityRect.height = sizeComponent.Height;
                if(entityRect.contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                {
                    i.getComponent<ChangeableComponent>().changeble = true;
                }
                else
                {
                    i.getComponent<ChangeableComponent>().changeble = false;
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
            if (i.hasComponent<ChangeableComponent>())
            {
                i.getComponent<ChangeableComponent>().changeble = false;
            }
        }
    }

    return false;
}



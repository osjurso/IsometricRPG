#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "include/states/state_menu.h"
#include "include/gameEngine/resource_holder.h"
#include "include/util/utility.h"

StateMenu::StateMenu(StateStack& stack, Context context)
        : StateBase(stack, context)
        , mOptions()
        , mOptionIndex(0)
{
    sf::Font& font = context.fonts->get(Fonts::Main);

    mLogoSprite.setTexture(context.textures->get(Textures::TitleText));
    mBackdrop.setTexture(context.textures->get(Textures::MenuBackdrop));
    mFire.setTexture(context.textures->get(Textures::MenuFire));

    fireSpriteSize = 265;

    spriteRect.top = 0;
    spriteRect.left = 0;
    spriteRect.height = fireSpriteSize;
    spriteRect.width = fireSpriteSize;

    clock.restart();
    mFire.setTextureRect(spriteRect);


    centerOrigin(mLogoSprite);
    mLogoSprite.setPosition(context.window->getSize().x / 2, context.window->getSize().y / 4);
    mBackdrop.setPosition(0,0);

    mFire2 = mFire;

    mFire.setPosition(530,90); //TODO: do dynamacly
    mFire2.setPosition(1130,90);

    // Creating menu choices
    sf::Text playOption;
    playOption.setFont(font);
    playOption.setString("Play");
    centerOrigin(playOption);
    playOption.setPosition(context.window->getView().getSize() / 2.f);
    playOption.move(0,-250);
    mOptions.push_back(playOption);

    sf::Text settingsOption;
    settingsOption.setFont(font);
    settingsOption.setString("Settings");
    centerOrigin(settingsOption);
    settingsOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 35.f));
    mOptions.push_back(settingsOption);

    sf::Text aboutOption;
    aboutOption.setFont(font);
    aboutOption.setString("About");
    centerOrigin(aboutOption);
    aboutOption.setPosition(settingsOption.getPosition() + sf::Vector2f(0.f, 35.f));
    mOptions.push_back(aboutOption);

    sf::Text exitOption;
    exitOption.setFont(font);
    exitOption.setString("Exit");
    centerOrigin(exitOption);
    exitOption.setPosition(aboutOption.getPosition() + sf::Vector2f(0.f, 35.f));
    mOptions.push_back(exitOption);

    updateOptionText();
}

void StateMenu::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(mLogoSprite);
    window.draw(mBackdrop);
    window.draw(mFire);
    window.draw(mFire2);

    for (const sf::Text& text : mOptions)
        window.draw(text);
}

bool StateMenu::update(sf::Time)
{
    if(clock.getElapsedTime().asSeconds() > 0.1f)
    {
        if(spriteRect.left == 3*fireSpriteSize)
        {
            StateMenu::spriteRect.left = 0;
            StateMenu::spriteRect.top += fireSpriteSize;
            if(spriteRect.top == 2*fireSpriteSize)
                spriteRect.top = 0;
        }else
            StateMenu::spriteRect.left += fireSpriteSize;

        mFire.setTextureRect(spriteRect);
        mFire2.setTextureRect(spriteRect);
        clock.restart();
    }

    return true;
}

bool StateMenu::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::Return)
    {
        if (mOptionIndex == Play)
        {
            requestStateChange(States::Game);
        }
        else if (mOptionIndex == Settings)
        {
            requestStateChange(States::Settings);
        }
        else if (mOptionIndex == About)
        {

        }
        else if (mOptionIndex == Exit)
        {
            requestStackPop();
        }
    }

    else if (event.key.code == sf::Keyboard::Up)
    {
        if (mOptionIndex > 0)
            mOptionIndex--;
        else
            mOptionIndex = mOptions.size() - 1;

        updateOptionText();
    }

    else if (event.key.code == sf::Keyboard::Down)
    {
        if (mOptionIndex < mOptions.size() - 1)
            mOptionIndex++;
        else
            mOptionIndex = 0;

        updateOptionText();
    }

    return true;
}

void StateMenu::updateOptionText()
{
    if (mOptions.empty())
        return;

    for (sf::Text& text : mOptions)
        text.setFillColor(sf::Color::White);

    mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}

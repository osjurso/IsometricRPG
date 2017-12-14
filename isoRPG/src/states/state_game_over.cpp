#include <util/utility.h>
#include <iostream>
#include "states/state_game_over.h"


StateGameOver::StateGameOver(StateStack &stack, StateBase::Context context)
        : StateBase(stack, context)
        , mOptionIndex(0)
        , titleFadeInStart(sf::seconds(0.0f))
        , titleFadeInLength(sf::seconds(4.0f))
        , titleFadeOutStart(sf::seconds(4.0f))
        , titleFadeOutLength(sf::seconds(8.0f))
        , fadeOutLength(sf::seconds(8.0f))
        , respawn(false)
{
    mTitleText.setFont(context.fonts->get(Fonts::RPG));
    mTitleText.setString("A villager found you passed out");
    mTitleText.setCharacterSize(56);
    mTitleText.setFillColor(sf::Color(0, 0, 0, 255));
    centerOrigin(mTitleText);
    mTitleText.setPosition(context.window->getView().getSize().x / 2,
                           context.window->getView().getSize().y / 3);

    backgroundShape.setFillColor(sf::Color(0, 0, 0, 255));
    backgroundShape.setSize(sf::Vector2f(getContext().window->getView().getSize()));

    getContext().music->play(Music::GameOver);

    clock.restart();
}

void StateGameOver::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(backgroundShape);

    window.draw(mTitleText);
}

bool StateGameOver::update(sf::Time dt)
{
    currentTime = clock.getElapsedTime();

    // Fade in the text
    if (currentTime < titleFadeInLength && !respawn)
    {
        const float ratio{ currentTime / titleFadeInLength };
        const sf::Color color(255, 255, 255, static_cast<sf::Uint8>(255.f * ratio));
        mTitleText.setFillColor(color);
    }

    //  Fade out the text
    if (currentTime > titleFadeOutStart && currentTime < titleFadeOutLength)
    {
        const float ratio{ (currentTime - titleFadeOutStart) / (titleFadeOutLength - titleFadeOutStart) };
        const sf::Color color(255, 255, 255, static_cast<sf::Uint8>(255.f * (1.f - ratio)));
        mTitleText.setFillColor(color);
    }

    // Change text and restart clock to begin fading again
    if (currentTime > titleFadeOutLength && !respawn)
    {
        mTitleText.setString("Press any key to respawn");
        centerOrigin(mTitleText);
        clock.restart();
    }

    // Fade out background
    if (respawn)
    {
        if (currentTime > titleFadeOutLength)
        {
            const float ratio{ (currentTime - fadeOutLength) / (fadeOutLength - titleFadeOutLength) };
            const sf::Color color(0, 0, 0, static_cast<sf::Uint8>(255.f * (1.f - ratio)));
            backgroundShape.setFillColor(color);
        }

        // WHen fading is finished, pop the state to reveal the game state
        if (currentTime > fadeOutLength)
        {
            getContext().music->play(Music::Test);

            requestStackPop();
        }
    }

    return true;
}

bool StateGameOver::handleEvent(const sf::Event &event)
{
    if (event.type == event.Resized)
        backgroundShape.setSize(sf::Vector2f(getContext().window->getView().getSize()));

    if (event.type == sf::Event::KeyPressed && !respawn)
    {
        respawn = true;
        titleFadeOutStart = sf::seconds(0);
        titleFadeOutLength = sf::seconds(3);
        clock.restart();
    }

    return false;
}

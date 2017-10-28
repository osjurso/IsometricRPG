#include <SFML/Graphics/RenderWindow.hpp>

#include "include/states/state_pause.h"
#include "include/gameEngine/resource_holder.h"
#include "include/util/utility.h"

StatePause::StatePause(StateStack &stack, StateBase::Context context)
        : StateBase(stack, context)
{
    mPauseText.setFont(context.fonts->get(Fonts::RPG));
    mPauseText.setString("Game Paused");
    mPauseText.setCharacterSize(48);
    centerOrigin(mPauseText);
    mPauseText.setPosition(context.window->getSize().x/2,
                           context.window->getSize().y/2);
    
    // Creating menu choices
    sf::Text resumeOption;
    resumeOption.setFont(context.fonts->get(Fonts::RPG));
    resumeOption.setString("Resume Game");
    centerOrigin(resumeOption);
    resumeOption.setPosition(mPauseText.getPosition() + sf::Vector2f(0.f, 80.f));
    mOptions.push_back(resumeOption);

    sf::Text settingsOption;
    settingsOption.setFont(context.fonts->get(Fonts::RPG));
    settingsOption.setString("Settings");
    centerOrigin(settingsOption);
    settingsOption.setPosition(resumeOption.getPosition() + sf::Vector2f(0.f, 35.f));
    mOptions.push_back(settingsOption);

    sf::Text saveOption;
    saveOption.setFont(context.fonts->get(Fonts::RPG));
    saveOption.setString("Save Game");
    centerOrigin(saveOption);
    saveOption.setPosition(settingsOption.getPosition() + sf::Vector2f(0.f, 35.f));
    mOptions.push_back(saveOption);

    sf::Text exitOption;
    exitOption.setFont(context.fonts->get(Fonts::RPG));
    exitOption.setString("Exit to Menu");
    centerOrigin(exitOption);
    exitOption.setPosition(saveOption.getPosition() + sf::Vector2f(0.f, 35.f));
    mOptions.push_back(exitOption);

}

void StatePause::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));
    window.draw(backgroundShape);

    window.draw(mPauseText);

    for (const sf::Text& text : mOptions)
        window.draw(text);
}

bool StatePause::update(sf::Time dt)
{
    return false;
}

bool StatePause::handleEvent(const sf::Event &event)
{

    if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::Return)
    {
        if (mOptionIndex == resume)
        {
            requestStackPop();
        }
        else if (mOptionIndex == settings)
        {
            //requestStateChange(States::Settings);
        }
        else if (mOptionIndex == Save)
        {

        }
        else if (mOptionIndex == exit)
        {
            requestStateClear();
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

    return false;
}

void StatePause::updateOptionText()
{
    if (mOptions.empty())
        return;

    for (sf::Text& text : mOptions)
        text.setFillColor(sf::Color::White);

    mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}

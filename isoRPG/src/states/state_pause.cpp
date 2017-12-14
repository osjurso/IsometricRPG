#include <SFML/Graphics/RenderWindow.hpp>

#include "states/state_pause.h"
#include "util/utility.h"

StatePause::StatePause(StateStack &stack, StateBase::Context context)
        : StateBase(stack, context)
        , mOptionIndex(0)

{
    mPauseText.setFont(context.fonts->get(Fonts::RPG));
    mPauseText.setString("Game Paused");
    mPauseText.setCharacterSize(48);
    centerOrigin(mPauseText);
    mPauseText.setPosition(context.window->getView().getSize().x / 2,
                           context.window->getView().getSize().y * 0.3f);
    
    // Creating menu choices
    sf::Text resumeOption;
    resumeOption.setFont(context.fonts->get(Fonts::RPG));
    resumeOption.setString("Resume Game");
    centerOrigin(resumeOption);
    resumeOption.setPosition(mPauseText.getPosition() + sf::Vector2f(0.f, 80.f));
    mOptions.push_back(resumeOption);

    sf::Text exitOption;
    exitOption.setFont(context.fonts->get(Fonts::RPG));
    exitOption.setString("Exit to Menu");
    centerOrigin(exitOption);
    exitOption.setPosition(resumeOption.getPosition() + sf::Vector2f(0.f, 35.f));
    mOptions.push_back(exitOption);

    updateOptionText();

    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sf::Vector2f(getContext().window->getView().getSize()));

    getContext().music->setPaused(true);
}

StatePause::~StatePause()
{
    getContext().music->setPaused(false);
}

void StatePause::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

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

    if (event.type == event.Resized)
        backgroundShape.setSize(sf::Vector2f(getContext().window->getView().getSize()));

    if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::Return)
    {
        if (mOptionIndex == resume)
        {
            requestStackPop();
        }
        else if (mOptionIndex == exit)
        {
            requestStackPop();
            requestStateChange(States::Menu);
        }
    }

    else if (event.key.code == sf::Keyboard::Up)
    {
        if (mOptionIndex > 0)
            mOptionIndex--;
        else
            mOptionIndex = mOptions.size() - 1;

        updateOptionText();
        getContext().sounds->play(SoundEffects::Click);
    }

    else if (event.key.code == sf::Keyboard::Down)
    {
        if (mOptionIndex < mOptions.size() - 1)
            mOptionIndex++;
        else
            mOptionIndex = 0;

        updateOptionText();
        getContext().sounds->play(SoundEffects::Click);
    }

    else if (event.key.code == sf::Keyboard::Escape)
        requestStackPop();

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

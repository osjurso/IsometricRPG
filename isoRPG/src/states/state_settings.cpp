#include <SFML/Graphics/RenderWindow.hpp>

#include "include/states/state_settings.h"
#include "include/gameEngine/resource_holder.h"

StateSettings::StateSettings(StateStack &stack, StateBase::Context context)
        : StateBase(stack, context)
{
    mTempText.setFont(context.fonts->get(Fonts::Main));
    mTempText.setString("Do something here");
}


void StateSettings::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.draw(mTempText);
}

bool StateSettings::update(sf::Time dt)
{
    return true;
}

bool StateSettings::handleEvent(const sf::Event &event)
{
    if (event.type != sf::Event::KeyPressed)
        return false;

        if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Menu);
    }

    return true;
}

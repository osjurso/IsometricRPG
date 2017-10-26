#include <SFML/Graphics/RenderWindow.hpp>

#include "include/states/state_pause.h"
#include "include/gameEngine/resource_holder.h"
#include "include/util/utility.h"

StatePause::StatePause(StateStack &stack, StateBase::Context context)
        : StateBase(stack, context)
{
    mPauseText.setFont(context.fonts->get(Fonts::Main));
    mPauseText.setString("The game is Paused (work in progress ...)");
    centerOrigin(mPauseText);
    mPauseText.setPosition(context.window->getSize().x/2,
                           context.window->getSize().y/2);
}

void StatePause::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.clear();
    window.setView(window.getDefaultView());

    window.draw(mPauseText);
}

bool StatePause::update(sf::Time dt) {
    return false;
}

bool StatePause::handleEvent(const sf::Event &event) {

    if (event.key.code == sf::Keyboard::Escape && event.type == sf::Event::KeyPressed)
        requestStackPop();

    return false;
}

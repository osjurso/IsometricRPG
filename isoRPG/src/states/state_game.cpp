#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "states/state_game.h"
#include "gameEngine/resource_holder.h"
#include "map/map.h"
#include "util/utility.h"



StateGame::StateGame(StateStack &stack, StateBase::Context context)
        : StateBase(stack, context)
        , playerCam()
{
    isMovingUp = false;
    isMovingDown = false;
    isMovingLeft = false;
    isMovingRight = false;

    playerCam.setSize(1920, 1080);
    playerCam.zoom(0.3f);

    // Load map information from JSON into object list
    if (!Map::load("assets/map/map.json", objects))
        std::runtime_error("StateGame::StateGame - Failed to load map data.");

    mPlayer.setTexture(context.textures->get(Textures::Hero));
    mPlayer.setOrigin(mPlayer.getGlobalBounds().width/2, mPlayer.getGlobalBounds().height*0.8);

    mPlayer.setPosition(0, 0);
}

void StateGame::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(playerCam);

    //Sorting objects based on priority (y coordinate), from low to high.
    objects.sort([](Object *f, const Object *s) { return f->priority < s->priority; });

    sf::CircleShape origin;
    origin.setRadius(1);
    origin.setFillColor(sf::Color::Green);
    origin.setPosition(mPlayer.getPosition());

    bool drawn = false;
    for (Object* object : objects)
    {
        object->process(1.f/60.f);
        object->draw(window);
        if (object->priority < mPlayer.getPosition().y)
        {
            window.draw(mPlayer);
            drawn = true;
        }
    }
    window.draw(origin);
}

bool StateGame::update(sf::Time dt)
{
    sf::Vector2f movement(0.f, 0.f);
    if (isMovingUp)
        movement.y -= 2.f;
    if (isMovingDown)
        movement.y += 2.f;
    if (isMovingLeft)
        movement.x -= 2.f;
    if (isMovingRight)
        movement.x += 2.f;

    mPlayer.move(movement);

    playerCam.setCenter(mPlayer.getPosition());

    return true;
}

bool StateGame::handleEvent(const sf::Event &event)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed:
            handleUserInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handleUserInput(event.key.code, false);
            break;
    }

    return true;
}

void StateGame::handleUserInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W)
        isMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        isMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        isMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        isMovingRight = isPressed;
    else if (key == sf::Keyboard::Escape && isPressed)
        requestStackPush(States::Pause);
    else if (key == sf::Keyboard::F5 && isPressed)
    {
        objects.clear();
        std::cout << "Loading map data ..." << std::endl;
        if (!Map::load("assets/map/map.json", objects))
        {
            std::cout << "Failed to reload map data." << std::endl;
        }
    }
}
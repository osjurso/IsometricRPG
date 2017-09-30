#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "include/states/state_game.h"
#include "include/gameEngine/resource_holder.h"
#include "include/map/map.h"
#include "include/util/utility.h"

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
    if (!Map::load("assets/map/IsoRPG.json", objects))
        std::runtime_error("StateGame::StateGame - Failed to load map data.");


    mPlayer.setTexture(context.textures->get(Textures::Hero));
    centerOrigin(mPlayer);
    mPlayer.setWorldPosition(100.f, 100.f);
    //mPlayer.setPosition(100.f, 100.f);
}

void StateGame::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(playerCam);

    for (Object* object : objects)
    {
        object->process(1.f/60.f);
        object->draw(window);
    }

    window.draw(mPlayer);
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
    else if (key == sf::Keyboard::Escape)
        requestStackPush(States::Pause);
    else if (key == sf::Keyboard::F5)
    {
        objects.clear();
        std::cout << "Loading map data ..." << std::endl;
        if (!Map::load("data/IsoRPG.json", objects))
            std::runtime_error("StateGame::StateGame - Failed to load map data.");
    }
}

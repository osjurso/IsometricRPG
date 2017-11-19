#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <include/systems/resolve_movment.h>
#include <include/systems/drawEntety.h>
#include <include/collections/setUpPlayer.h>

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
/*
    mPlayer.setTexture(context.textures->get(Textures::Hero));
    mPlayer.setOrigin(mPlayer.getGlobalBounds().width/2, mPlayer.getGlobalBounds().height*0.8);

    mPlayer.setPosition(0, 0);
*/

    sf::Texture& Herobody = context.textures->get(Textures::Hero);
    sf::Texture& HeroHead = context.textures->get(Textures::HeroHead);
    sf::Texture& HeroWeapon = context.textures->get(Textures::HeroWeapon);
    sf::Texture& HeroShield = context.textures->get(Textures::HeroShield);

    anax::World& world = *getContext().world;
    sf::RenderWindow& window = *getContext().window;
    DrawEntetys drawEntetys;
    drawEntetys.draw(window,world, "Game");
    player = world.createEntity();

    SetUpPlayer playerSetup;
    playerSetup.setUpPlayer(player, Herobody, HeroHead, HeroWeapon,HeroShield, *getContext().window);
    context.music->play(Music::Test);
}

void StateGame::draw()

{

    sf::RenderWindow& window = *getContext().window;

    window.setView(playerCam);

    //Sorting objects based on priority (y coordinate), from low to high.
    objects.sort([](Object *f, const Object *s) { return f->priority < s->priority; });

    anax::World& world = *getContext().world;
    DrawEntetys drawEntetys;

    for (Object* object : objects)
    {
        object->process(1.f/60.f);
        object->draw(window);
        if (object->priority < mPlayer.getPosition().y)
            window.draw(mPlayer);
    }
    drawEntetys.draw(window,world, "Game");
}

bool StateGame::update(sf::Time dt)
{
    AnimationComponent& animationComponent = player.getComponent<AnimationComponent>();
    ResolveMovment resolve;
    float deltaTime = animationComponent.animationClock.restart().asSeconds();

    if(animationComponent.idleTimer.getElapsedTime().asSeconds() >= 0.2f && animationComponent.idle == false) {
        if(animationComponent.direction != "Idle" )animationComponent.changedDirection = true;
        animationComponent.direction = "Idle";
        float deltaTime = animationComponent.animationClock.restart().asSeconds();
        resolve.resolveMovment(player, "Idle", deltaTime);

        PositionComponent& positionComponent = player.getComponent<PositionComponent>();
        Moveble& moveble = player.getComponent<Moveble>();
    }
    animationComponent.animationClock.restart().asSeconds();

    PositionComponent& positionComponent = player.getComponent<PositionComponent>();
    playerCam.setCenter(positionComponent.XPos, positionComponent.YPos);


    std::cout<< "XPOS:  " << animationComponent.currentImage.x << std::endl;

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
    ResolveMovment resolve;
    AnimationComponent& animationComponent = player.getComponent<AnimationComponent>();
    float deltaTime = animationComponent.animationClock.restart().asSeconds();

    //animationComponent.animationClock.restart().asSeconds();


    if (key == sf::Keyboard::W|| key == sf::Keyboard::Up)
    {
        animationComponent.idleTimer.restart().asSeconds();
        animationComponent.idle = false;
        if(animationComponent.direction != "Up" )animationComponent.changedDirection = true;
        animationComponent.direction = "Up";
        animationComponent.movementDirection.y -= animationComponent.movementSpeed*animationComponent.deltaTime;
        animationComponent.row = 2;
        resolve.resolveMovment(player, "Walk", deltaTime);

        PositionComponent& positionComponent = player.getComponent<PositionComponent>();
        Moveble moveble = player.getComponent<Moveble>();
        positionComponent.YPos -= moveble.speed;
        isMovingUp = isPressed;
    }

    else if (key == sf::Keyboard::S|| key == sf::Keyboard::Down)
    {
        animationComponent.idleTimer.restart().asSeconds();
        animationComponent.idle = false;
        if(animationComponent.direction != "Down" )animationComponent.changedDirection = true;
        animationComponent.direction = "Down";
        animationComponent.movementDirection.y += animationComponent.movementSpeed*animationComponent.deltaTime;
        animationComponent.row = 6;
        resolve.resolveMovment(player, "Walk", deltaTime);

        PositionComponent& positionComponent = player.getComponent<PositionComponent>();
        Moveble moveble = player.getComponent<Moveble>();
        positionComponent.YPos += moveble.speed;
        isMovingDown = isPressed;
    }

    else if (key == sf::Keyboard::A || key == sf::Keyboard::Left)
    {
        animationComponent.idleTimer.restart().asSeconds();
        animationComponent.idle = false;
        if(animationComponent.direction != "Left" )animationComponent.changedDirection = true;
        animationComponent.direction = "Left";
        animationComponent.movementDirection.x -= animationComponent.movementSpeed*animationComponent.deltaTime;
        animationComponent.row = 0;
        resolve.resolveMovment(player, "Walk", deltaTime);

        PositionComponent& positionComponent = player.getComponent<PositionComponent>();
        Moveble moveble = player.getComponent<Moveble>();
        positionComponent.XPos -= moveble.speed;

        isMovingDown = isPressed;
    }

    else if (key == sf::Keyboard::D || key == sf::Keyboard::Right)
    {
        animationComponent.idleTimer.restart().asSeconds();
        animationComponent.idle = false;
        if(animationComponent.direction != "Right" )animationComponent.changedDirection = true;
        animationComponent.direction = "Right";
        animationComponent.movementDirection.x += animationComponent.movementSpeed*animationComponent.deltaTime;
        animationComponent.row = 4;
        resolve.resolveMovment(player, "Walk", deltaTime);

        PositionComponent& positionComponent = player.getComponent<PositionComponent>();
        Moveble moveble = player.getComponent<Moveble>();
        positionComponent.XPos += moveble.speed;

        isMovingRight = isPressed;
    }

        //Attack method
    else if (key == sf::Keyboard::V)
    {
        animationComponent.idleTimer.restart().asSeconds();
        animationComponent.idle = false;
        if(animationComponent.direction != "Attack" )animationComponent.changedDirection = true;
        animationComponent.direction = "Attack";
        animationComponent.movementDirection.x += animationComponent.movementSpeed*animationComponent.deltaTime;
        //animationComponent.row = 4;
        resolve.resolveMovment(player, "Attack", deltaTime);

        PositionComponent& positionComponent = player.getComponent<PositionComponent>();

        isMovingRight = isPressed;
    }

        //Defend method
    else if (key == sf::Keyboard::B)
    {
        animationComponent.idleTimer.restart().asSeconds();
        animationComponent.idle = false;
        if(animationComponent.direction != "Defend" )animationComponent.changedDirection = true;
        animationComponent.direction = "Defend";
        animationComponent.movementDirection.x += animationComponent.movementSpeed*animationComponent.deltaTime;
        //animationComponent.row = 4;
        resolve.resolveMovment(player, "Defend", deltaTime);

        PositionComponent& positionComponent = player.getComponent<PositionComponent>();
        isMovingRight = isPressed;
    }




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
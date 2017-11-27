#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>

#include <systems/sort_key_update.h>
#include "systems/resolve_movment.h"
#include "systems/drawEntety.h"
#include "systems/attack.h"
#include <systems/resolvePositionChange.h>
#include <systems/resolve_agro.h>
#include <systems/generatePath.h>
#include "systems/mouse_clicked.h"

#include "collections/setUpCreature.h"
#include "collections/addDialoge.h"


#include "states/state_game.h"
#include "map/map.h"
#include "util/utility.h"

StateGame::StateGame(StateStack &stack, StateBase::Context context)
        : StateBase(stack, context)
        , playerCam()
{
    anax::World& world = *getContext().world;
    playerCam.setSize(1920, 1080);
    playerCam.zoom(0.3f);
    player = world.createEntity();

    // Load map information from JSON into object list
    if (!Map::load("assets/map/map.json", objects, context))
        std::runtime_error("StateGame::StateGame - Failed to load map data.");

    sf::Texture& Herobody = context.textures->get(Textures::Hero);
    sf::Texture& GoblinTexture = context.textures->get(Textures::Goblin);
    sf::Texture& TraderTexture = context.textures->get(Textures::Trader);
    sf::Texture& HeroHead = context.textures->get(Textures::HeroHead);
    sf::Texture& HeroWeapon = context.textures->get(Textures::HeroWeapon);
    sf::Texture& HeroShield = context.textures->get(Textures::HeroShield);
    player.addComponent<TextureComponent>();
    TextureComponent& textureComponent = player.getComponent<TextureComponent>();
    textureComponent.texture[0] = Herobody;
    textureComponent.sprite[0].setTexture(textureComponent.texture[0]);
    textureComponent.texture[1] = HeroHead;
    textureComponent.sprite[1].setTexture(textureComponent.texture[1]);
    textureComponent.texture[2] = HeroWeapon;
    textureComponent.sprite[2].setTexture(textureComponent.texture[2]);
    textureComponent.texture[3] = HeroShield;
    textureComponent.sprite[3].setTexture(textureComponent.texture[3]);


    movementTimer.restart().asSeconds();
    pathfindingTimer.restart().asSeconds();


    sf::RenderWindow& window = *getContext().window;
    DrawEntetys drawEntetys;


    anax::Entity goblin = world.createEntity();
    anax::Entity goblin2 = world.createEntity();
    anax::Entity goblin3 = world.createEntity();
    anax::Entity goblin4 = world.createEntity();
    anax::Entity trader = world.createEntity();

    SetUpCreature creatureSetup;

    creatureSetup.setUpPlayer(player,window);
    creatureSetup.setUpEnemie(goblin,  GoblinTexture, *getContext().window, 200, 200, "Hard");
    creatureSetup.setUpEnemie(goblin2, GoblinTexture, *getContext().window ,100 ,100, "Medium");
    creatureSetup.setUpEnemie(goblin3, GoblinTexture, *getContext().window ,400 ,200, "Easy");
    creatureSetup.setUpEnemie(goblin4, GoblinTexture, *getContext().window ,300 ,100, "Hard");
    creatureSetup.setUpNPC(trader,TraderTexture,*getContext().window,300,300);

    sf::Font& font = context.fonts->get(Fonts::Main);
    playerGold.setFont(font);
    playerGold.setScale(0.3,0.3);
    sf::Color gold(255,215,0);
    playerGold.setFillColor(gold);

    AddDialoge addDialoge;
    addDialoge.addDialoge(trader,"assets/dialog/trader_dialog_1.txt");
    context.music->play(Music::Test);

}

void StateGame::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(playerCam);

    anax::World& world = *getContext().world;
    DrawEntetys drawEntetys;

    drawEntetys.draw(window,world, "Game");
    Looteble looteble = player.getComponent<Looteble>();
    sf::Vector2f viewCenter = window.getView().getCenter();
    sf::Vector2f halfExtents = window.getView().getSize() / 2.0f;
    sf::Vector2f translation = viewCenter - halfExtents;

    int mX = static_cast<int>(translation.x);
    int mY = static_cast<int>(translation.y);

    playerGold.setPosition(mX +5 ,mY +5);
    playerGold.setString(std::to_string(looteble.gold));
    window.draw(playerGold);


}

bool StateGame::update(sf::Time dt)
{
    AnimationComponent& animationComponent = player.getComponent<AnimationComponent>();
    ResolveMovment resolve;
    float deltaTime = animationComponent.animationClock.restart().asSeconds();

    if(animationComponent.idleTimer.getElapsedTime().asSeconds() >= 0.2f && animationComponent.idle == false) {
        animationComponent.action = "Idle";
        if(animationComponent.direction != "Idle" )animationComponent.changedDirection = true;
        animationComponent.direction = "Idle";
        float deltaTime = animationComponent.animationClock.restart().asSeconds();
    }
    animationComponent.animationClock.restart().asSeconds();

    PositionComponent& positionComponent = player.getComponent<PositionComponent>();
    playerCam.setCenter(positionComponent.SpriteLeft, positionComponent.SpriteTop);


    if(movementTimer.getElapsedTime().asSeconds() >= 0.05f)
    {
        float deltaTime = movementTimer.getElapsedTime().asSeconds();

        PostitonChange postitonChange;
        postitonChange.change(*getContext().world, player);

        ResolveAgro resolveAgro;
        resolveAgro.agro(player, *getContext().world);


        resolve.resolveMovment(*getContext().world, deltaTime);


        movementTimer.restart().asSeconds();
    }
    if(pathfindingTimer.getElapsedTime().asSeconds() >= 0.5)
    {
        GeneratePath generatePath;
        generatePath.generate(*getContext().world,player);

        pathfindingTimer.restart();
    }


    // Update the sort key for movable entities
    SortKeyUpdate sortKeyUpdate;
    sortKeyUpdate.Update(*getContext().world);

    return true;
}

bool StateGame::handleEvent(const sf::Event &event)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        anax::World& world = *getContext().world;
        sf::RenderWindow& window = *getContext().window;
        MouseClicked mouseClicked;
        mouseClicked.Clicked(world, player, window, playerCam);

    }

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
    Movable& movable = player.getComponent<Movable>();

    animationComponent.animationClock.restart().asSeconds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A)) animationComponent.action = "Walk";

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 7;
            movable.path = "7";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 5;
            movable.path = "5";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 1;
            movable.path = "1";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 3;
            movable.path = "3";
        }

        if (key == sf::Keyboard::W || key == sf::Keyboard::Up) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 6;
            movable.path = "6";

        } else if (key == sf::Keyboard::S || key == sf::Keyboard::Down) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 2;
            movable.path = "222";

        } else if (key == sf::Keyboard::A || key == sf::Keyboard::Left) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 4;
            movable.path = "4";

        } else if (key == sf::Keyboard::D || key == sf::Keyboard::Right) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 0;
            movable.path = "0";
        }


        //Attack method
    else if (key == sf::Keyboard::V)
    {
        animationComponent.action = "Attack";
        animationComponent.idleTimer.restart().asSeconds();
        animationComponent.idle = false;
        if(animationComponent.direction != "Attack" )animationComponent.changedDirection = true;
        animationComponent.direction = "Attack";

        PositionComponent& positionComponent = player.getComponent<PositionComponent>();
    }

        //Defend method
    else if (key == sf::Keyboard::B)
    {
        animationComponent.action = "Defend";
        animationComponent.idleTimer.restart().asSeconds();
        animationComponent.idle = false;
        if(animationComponent.direction != "Defend" )animationComponent.changedDirection = true;
        animationComponent.direction = "Defend";

        PositionComponent& positionComponent = player.getComponent<PositionComponent>();
    }
    else if (key == sf::Keyboard::Space)
    {
        Attack attack;
        anax::World& world = *getContext().world;
        attack.resolveAttack(world,player);
    }

    else if (key == sf::Keyboard::Escape && isPressed)
        requestStackPush(States::Pause);
    else if (key == sf::Keyboard::F5 && isPressed)
    {
        objects.clear();
        std::cout << "Loading map data ..." << std::endl;
        if (!Map::load("assets/map/map.json", objects, getContext()))
        {
            std::cout << "Failed to reload map data." << std::endl;
        }
    }
}
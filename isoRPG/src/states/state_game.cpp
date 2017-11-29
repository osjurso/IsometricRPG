#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>

#include <systems/sort_key_update.h>
#include "systems/resolve_movment.h"
#include "systems/drawEntety.h"
#include "systems/attack.h"
#include <systems/resolvePositionChange.h>
#include <systems/resolve_agro.h>
#include <systems/generatePath.h>
#include <include/collections/drawable.h>
#include <include/components/Comp_UI.h>
#include <include/systems/update_UI.h>
#include <include/collections/drawebleText.h>
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
    float zoom = 0.3f;
    anax::World& world = *getContext().world;
    playerCam.setSize(1920, 1080);
    playerCam.zoom(zoom);

    player = world.createEntity();

    // Load map information from JSON into object list
    if (!Map::load("assets/map/map.json", objects, context))
        std::runtime_error("StateGame::StateGame - Failed to load map data.");

    // TODO get under one function: setUpCreatures
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

    //TODO get under one function: set up UI

    anax::Entity bottom = world.createEntity();
    anax::Entity items = world.createEntity();

    bottom.addComponent<UIComp>();
    items.addComponent<UIComp>();

    bottom.getComponent<UIComp>().Yofset = -60;
    items.getComponent<UIComp>().Yofset = -50;
    items.getComponent<UIComp>().Xofset = 400;

    sf::Texture& bottomTexture = context.textures->get(Textures::UIBottom);
    sf::Texture& itemTexture = context.textures->get(Textures::UIItems);

    Draweble draweble;
    draweble.makeDraweble(itemTexture,0, 0, items,"Game");
    items.getComponent<TextureComponent>().sprite->setScale(zoom,zoom);

    draweble.makeDraweble(bottomTexture,0,0, bottom,"Game");
    bottom.getComponent<TextureComponent>().sprite->setScale(zoom,zoom);

    bottom.getComponent<TextureComponent>().sortKey = 1000;
    items.getComponent<TextureComponent>().sortKey = 1001;



    sf::Font font = getContext().fonts->get(Fonts::RPG);
    sf::Color gold(255,215,0);
    sf::Color steel(67, 70, 75);
    sf::Color potionRed(230, 0, 27);

    anax::Entity HPotionCount = world.createEntity();
    anax::Entity GoldCount = world.createEntity();
    anax::Entity ArmorCount = world.createEntity();
    anax::Entity WeaponCount = world.createEntity();

    DrawebleText drawebleText;
    std::string nrPotion = "x "+ std::to_string(3);
    std::string nrGold = "x "+ std::to_string(player.getComponent<Looteble>().gold);
    std::string nrArmor = "10 + "+ std::to_string(0);
    std::string nrSword = "10 + "+ std::to_string(0);


    drawebleText.setUpDrawebleText(HPotionCount ,nrPotion, playerCam, "Game", zoom,font,potionRed);
    drawebleText.setUpDrawebleText(GoldCount ,nrGold, playerCam, "Game", zoom,font,gold);
    drawebleText.setUpDrawebleText(ArmorCount ,nrArmor, playerCam, "Game", zoom,font,steel);
    drawebleText.setUpDrawebleText(WeaponCount ,nrSword, playerCam, "Game", zoom,font,steel);

    HPotionCount.getComponent<UIComp>().Xofset = 425;
    HPotionCount.getComponent<UIComp>().Yofset = -45;
    HPotionCount.getComponent<TextComponent>().content = "Potion";

    GoldCount.getComponent<UIComp>().Xofset = 425;
    GoldCount.getComponent<UIComp>().Yofset = -20;
    GoldCount.getComponent<TextComponent>().content = "Gold";

    ArmorCount.getComponent<UIComp>().Xofset = 500;
    ArmorCount.getComponent<UIComp>().Yofset = -20;
    ArmorCount.getComponent<TextComponent>().content = "Armor";

    WeaponCount.getComponent<UIComp>().Xofset = 500;
    WeaponCount.getComponent<UIComp>().Yofset = -45;
    ArmorCount.getComponent<TextComponent>().content = "Weapon";




    AddDialoge addDialoge;
    //addDialoge.addDialoge(trader,"assets/dialog/trader_dialog_1.txt");
    context.music->play(Music::Test);

}

void StateGame::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(playerCam);

    anax::World& world = *getContext().world;

    DrawEntetys drawEntetys;
    drawEntetys.draw(window,world, "Game");

    sf::Vector2f viewCenter = window.getView().getCenter();
    sf::Vector2f halfExtents = window.getView().getSize() / 2.0f;
    sf::Vector2f translation = viewCenter - halfExtents;

    int mX = static_cast<int>(translation.x);
    int mY = static_cast<int>(translation.y);




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



    if(movementTimer.getElapsedTime().asSeconds() >= 0.05f)
    {
        float deltaTime = movementTimer.getElapsedTime().asSeconds();

        PostitonChange postitonChange;
        postitonChange.change(*getContext().world, player);

        ResolveAgro resolveAgro;
        resolveAgro.agro(player, *getContext().world);


        resolve.resolveMovment(*getContext().world, deltaTime);

        playerCam.setCenter(positionComponent.SpriteLeft, positionComponent.SpriteTop);
        movementTimer.restart().asSeconds();
    }
    if(pathfindingTimer.getElapsedTime().asSeconds() >= 0.5f)
    {
        GeneratePath generatePath;
        generatePath.generate(*getContext().world,player);

        pathfindingTimer.restart();
    }

    UpdateUI updateUI;
    updateUI.update(*getContext().world, playerCam, player);

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
        mouseClicked.Clicked(world, player, window, playerCam,getContext().fonts->get(Fonts::RPG));

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
    movable.path= "";
    float Xmove;
    float Ymove;
    char Dmove;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        animationComponent.action = "Walk";
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 7;
            Xmove = 0.5;
            Ymove = -0.5;
            Dmove = '7';

        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 5;
            Xmove = -0.5;
            Ymove = -0.5;
            Dmove = '5';
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 1;
            Xmove = 0.5;
            Ymove = 0.5;
            Dmove = '1';
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 3;
            Xmove = 0.5;
            Ymove = -0.5;
            Dmove = '3';
            movable.path= "3";
        }else if (key == sf::Keyboard::W || key == sf::Keyboard::Up) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 6;
            Xmove = 0;
            Ymove = -1;
            Dmove = '6';

        }else if (key == sf::Keyboard::S || key == sf::Keyboard::Down) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 2;
            Xmove = 0;
            Ymove = 1;
            Dmove = '2';

        } else if (key == sf::Keyboard::A || key == sf::Keyboard::Left) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 4;
            Xmove = -1;
            Ymove = 0;
            Dmove = '4';

        } else if (key == sf::Keyboard::D || key == sf::Keyboard::Right) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 0;
            Xmove = 1;
            Ymove = 0;
            Dmove = '0';
        }
        movable.path= "";
        for(int i = 0; i< movable.speed; i++)
        {
            movable.moveX[i] = Xmove;
            movable.moveY[i] = Ymove;
            movable.path.push_back(Dmove);
        }
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
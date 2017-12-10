#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>

#include <systems/depth_sort_system.h>
#include "systems/resolve_movment.h"
#include "systems/drawEntety.h"
#include "systems/attack.h"
#include <systems/resolvePositionChange.h>
#include <systems/resolve_agro.h>
#include <systems/generatePath.h>
#include <systems/update_UI.h>
#include "systems/mouse_clicked.h"

#include <components/Comp_UI.h>

#include <collections/drawebleText.h>
#include <collections/drawable.h>
#include <include/collections/addDialogOption.h>
#include <include/systems/killdying.h>
#include <include/components/Comp_ActionTimers.h>
#include <systems/UpdateDialog.h>
#include <include/systems/UpdateDialog.h>
#include <include/components/CompCost.h>
#include <include/collections/setUpAllCreatures.h>
#include <include/components/Comp_save.h>
#include <include/systems/resolveIAI_attack.h>
#include "collections/setUpUI.h"
#include "collections/setUpCreature.h"
#include "collections/addDialoge.h"
#include "collections/mouseClikedFunctions.h"


#include "states/state_game.h"
#include "map/map.h"
#include "util/utility.h"


StateGame::StateGame(StateStack &stack, StateBase::Context context)
        : StateBase(stack, context)
        , playerCam()
        , m_lightingSystem(context.textures->get(Textures::LightTexture))
{
    zoom = 0.3f;
    anax::World& world = *getContext().world;
    playerCam = context.window->getView();
    playerCam.setSize(1920, 1080);
    playerCam.zoom(zoom);

    auto entitys = world.getEntities();
    for(auto i : entitys)
    {
        if(i.hasComponent<SaveComponent>())
        {
            if(i.getComponent<SaveComponent>().number != -1)
            {
                save = i.getComponent<SaveComponent>().number;
                saveFile = i.getComponent<SaveComponent>().file;
                std::cout << saveFile << std::endl;
                i.kill();
                world.refresh();
            }
        }
    }

    player = world.createEntity();

    // Load map information from JSON into object list
    if (!Map::load("assets/map/map.json", context, m_lightingSystem))
        std::runtime_error("StateGame::StateGame - Failed to load map data.");

    setUpAllCreatures setUpAllCreatures(getContext());
    setUpAllCreatures.SetUpCreatures(player);
    if(save != -1)
    {
        int nr = 0;
        std::map<int, std::string> SaveText;
        std::ifstream file(saveFile);
        std::string tempstring;
        while (std::getline(file, tempstring))
        {
            SaveText[nr] = tempstring;
            nr++;
        }
        std::string name = SaveText[0];
        player.getComponent<Looteble>().name = name;

        std::string gold = SaveText[1];
        int goldNumber;
        std::istringstream ( gold ) >> goldNumber;
        player.getComponent<Looteble>().gold = goldNumber;

        std::string HealtPotion = SaveText[2];
        int HealtPotionNumber;
        std::istringstream ( HealtPotion ) >> HealtPotionNumber;
        player.getComponent<Looteble>().HealtPotion = HealtPotionNumber;

        std::string Armor = SaveText[3];
        int ArmorNumber;
        std::istringstream ( Armor ) >> ArmorNumber;
        player.getComponent<Looteble>().armor = ArmorNumber;

        std::string ArmorMod = SaveText[4];
        int ArmorModNumber;
        std::istringstream ( ArmorMod ) >> ArmorModNumber;
        player.getComponent<Looteble>().armorModifier = ArmorModNumber;

        std::string Weapon = SaveText[5];
        int WeaponNumber;
        std::istringstream ( Weapon ) >> WeaponNumber;
        player.getComponent<Looteble>().weapon = WeaponNumber;

        std::string WeaponMod = SaveText[6];
        int WeaponModNumber;
        std::istringstream ( WeaponMod ) >> WeaponModNumber;
        player.getComponent<Looteble>().weaponModifier = WeaponModNumber;

        //TODO: add carecter color
        player.getComponent<TextureComponent>().sprite[0].setColor(sf::Color(100,255,255)); // makes good bluealternative

    }

    //read form file
    // 1. Name
    // 2. Gold
    // 3: Healt potion
    // 4. Armor
    // 5. Armor mod
    // 6. Weapon
    // 7. Weapon mod


    movementTimer.restart().asSeconds();
    pathfindingTimer.restart().asSeconds();
    saveTimer.restart().asSeconds();


    SetUpUI setUpUI;
    setUpUI.setUpUI(world,zoom,
                    context.textures->get(Textures::UIBottom),
                    context.textures->get(Textures::UIItems),
                    context.textures->get(Textures::UIAbilities),
                    context.textures->get(Textures::UIHealtBar),
                    context.textures->get(Textures::UITransparant),
                    getContext().fonts->get(Fonts::RPG),playerCam,player);


    world.addSystem(m_collisionSystem);

    context.music->play(Music::Test);
}

StateGame::~StateGame()
{
    getContext().world->clear();
}

void StateGame::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(playerCam);

    anax::World& world = *getContext().world;

    DrawEntetys drawEntetys;
    drawEntetys.draw(window,world, "Game");
    m_lightingSystem.draw(window, world);
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

    KillDying killDying;
    killDying.killDying(*getContext().world);


    if(movementTimer.getElapsedTime().asSeconds() >= 0.05f)
    {
        float deltaTime = movementTimer.getElapsedTime().asSeconds();

        PostitonChange postitonChange;
        postitonChange.change(*getContext().world, player);

        ResolveAgro resolveAgro;
        resolveAgro.agro(player, *getContext().world);


        resolve.resolveMovment(*getContext().world, deltaTime);

        playerCam.setCenter(positionComponent.SpriteLeft + player.getComponent<SizeComponent>().SpriteWhith/2, positionComponent.SpriteTop + player.getComponent<SizeComponent>().SpriteHeight/2);
        movementTimer.restart().asSeconds();

        UpdateUI updateUI;
        updateUI.update(*getContext().world, playerCam, player);
    }
    if(pathfindingTimer.getElapsedTime().asSeconds() >= 0.5f)
    {
        GeneratePath generatePath;
        generatePath.generate(*getContext().world,player);

        ResolveAIAttack resolveAIAttack;
        resolveAIAttack.resolve(*getContext().world,player);

        pathfindingTimer.restart();
    }
    if(saveTimer.getElapsedTime().asSeconds() >= 10)
    {
        std::ofstream ofs;
        ofs.open(saveFile, std::ofstream::out | std::ofstream::trunc);
        ofs << player.getComponent<Looteble>().name << std::endl;
        ofs << player.getComponent<Looteble>().gold << std::endl;
        ofs << player.getComponent<Looteble>().HealtPotion << std::endl;
        ofs << player.getComponent<Looteble>().armor << std::endl;
        ofs << player.getComponent<Looteble>().armorModifier << std::endl;
        ofs << player.getComponent<Looteble>().weapon << std::endl;
        ofs << player.getComponent<Looteble>().weaponModifier << std::endl;
        ofs.close();
    }
    //read form file
    // 1. Name
    // 2. Gold
    // 3: Healt potion
    // 4. Armor
    // 5. Armor mod
    // 6. Weapon
    // 7. Weapon mod


    UpdateDialog updateDialog;
    updateDialog.update(*getContext().world, *getContext().window, playerCam, zoom, getContext().fonts->get(Fonts::RPG), getContext().textures->get(Textures::UIConversation), getContext().textures->get(Textures::UIRedX),getContext().textures->get(Textures::UIArrow));

    // Update the sort key for movable entities
    DepthSortSystem depthSortSystem;
    depthSortSystem.Update(*getContext().world);

    m_collisionSystem.update(dt.asSeconds(), *getContext().world);

    return true;
}

bool StateGame::handleEvent(const sf::Event &event)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        MouseClicked mouseClicked(getContext());
        mouseClicked.Clicked(player, playerCam, zoom, "Game");
    }

    if (event.type == sf::Event::Resized)
    {
        std::cout << "New resolution: " << event.size.width << "x" << event.size.height << std::endl;
        playerCam = getLetterboxView(playerCam, event.size.width, event.size.height );
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

    animationComponent.idleTimer.restart().asSeconds();
    movable.path= "";
    float Xmove;
    float Ymove;
    char Dmove;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        movable.path= "";
        player.getComponent<AnimationComponent>().idleTimer.restart().asSeconds();
        animationComponent.action = "Walk";
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 7;
            Xmove = 0.66;
            Ymove = -0.33;
            Dmove = '7';

        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 5;
            Xmove = -0.66;
            Ymove = -0.33;
            Dmove = '5';
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 1;
            Xmove = 0.66;
            Ymove = 0.33;
            Dmove = '1';
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            animationComponent.idleTimer.restart().asSeconds();
            animationComponent.idle = false;
            animationComponent.animationDirection = 3;
            Xmove = -0.66;
            Ymove = 0.33;
            Dmove = '3';
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
        player.getComponent<AnimationComponent>().idleTimer.restart().asSeconds();
        for(int i = 0; i< movable.speed; i++)
        {
            movable.moveX[i] = Xmove;
            movable.moveY[i] = Ymove;
            movable.path.push_back(Dmove);
        }
    }

        //Attack method
    else if (key == sf::Keyboard::Space && player.getComponent<ActionTimer>().AttackTimer.getElapsedTime().asSeconds() > player.getComponent<ActionTimer>().AttackCooldown)
    {
        animationComponent.action = "Attack";
        animationComponent.idleTimer.restart().asSeconds();
        animationComponent.idle = false;
        if(animationComponent.direction != "Attack" )animationComponent.changedDirection = true;
        animationComponent.direction = "Attack";

        PositionComponent& positionComponent = player.getComponent<PositionComponent>();

        Attack attack;
        anax::World& world = *getContext().world;
        attack.resolveAttack(world,player);

        player.getComponent<ActionTimer>().AttackTimer.restart().asSeconds();
    }

        //Defend method
    else if (key == sf::Keyboard::LShift)
    {
        animationComponent.action = "Defend";
        animationComponent.idleTimer.restart().asSeconds();
        animationComponent.idle = false;
        if(animationComponent.direction != "Defend" )animationComponent.changedDirection = true;
        animationComponent.direction = "Defend";

        PositionComponent& positionComponent = player.getComponent<PositionComponent>();
    }else if (key == sf::Keyboard::Q && player.getComponent<Looteble>().HealtPotion > 0 && player.getComponent<ActionTimer>().PotionTimer.getElapsedTime().asSeconds() > player.getComponent<ActionTimer>().PotionCooldown )
    {
        player.getComponent<Looteble>().HealtPotion -=1;
        player.getComponent<HealthComponent>().health += 200;
        if(player.getComponent<HealthComponent>().health > player.getComponent<HealthComponent>().maxHealth) player.getComponent<HealthComponent>().health = player.getComponent<HealthComponent>().maxHealth;
        player.getComponent<ActionTimer>().PotionTimer.restart().asSeconds();
    }

    else if (key == sf::Keyboard::Escape && isPressed)
        requestStackPush(States::Pause);
    else if (key == sf::Keyboard::F2 && isPressed)
        requestStackPush(States::GameOver);
    else if (key == sf::Keyboard::F5 && isPressed)
    {
        // Todo: Hvis vi skal bruke map reload må den også resette anax world

        std::cout << "Loading map data ..." << std::endl;
        if (!Map::load("assets/map/map.json", getContext(), m_lightingSystem))
        {
            std::cout << "Failed to reload map data." << std::endl;
        }
    }
}
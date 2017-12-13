#include <include/components/Comp_Children.h>
#include <include/components/Comp_ActionTimers.h>
#include <include/components/CompCost.h>
#include <include/components/Comp_Draweble.h>
#include <include/components/comp_collision.h>
#include <include/systems/collision_system.h>
#include "include/collections/setUpCreature.h"

void SetUpCreature::setUpPlayer(anax::Entity& entity, sf::RenderWindow& window)
{
    TextureComponent& textureComponent = entity.getComponent<TextureComponent>();
    textureComponent.spriteRect.height = 128;
    textureComponent.spriteRect.width = 128;
    textureComponent.multisprite = true;

    entity.addComponent<PositionComponent>();
    PositionComponent& positionComponent = entity.getComponent<PositionComponent>();

    positionComponent.YPos = 1650;
    positionComponent.XPos = -95;
    positionComponent.SpriteLeft =  positionComponent.XPos +95;
    positionComponent.SpriteTop =  positionComponent.YPos +95;

    entity.addComponent<SizeComponent>();
    SizeComponent& sizeComponent = entity.getComponent<SizeComponent>();
    sizeComponent.Height = textureComponent.spriteRect.height;
    sizeComponent.Whith = textureComponent.spriteRect.width;

    entity.addComponent<AnimationComponent>();
    AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();
    animationComponent.imageCounter.x = 32;
    animationComponent.imageCounter.y = 8;
    animationComponent.switchTime = 0.08f;
    animationComponent.pixels = 128;
    animationComponent.movementSpeed = 100;
    animationComponent.row =0;
    animationComponent.currentImage.x =0;
    animationComponent.animationClock.restart().asSeconds();
    animationComponent.idleStart = 0;
    animationComponent.idleEnd = 3;
    animationComponent.walkStart = 4;
    animationComponent.walkEnd = 11;
    animationComponent.attackStart = 12;
    animationComponent.attackEnd = 15;
    animationComponent.defendStart = 16;
    animationComponent.defendEnd = 17;

    animationComponent.rowWest = 0;
    animationComponent.rowNorthWest = 1;
    animationComponent.rowNorth = 2;
    animationComponent.rowNorthEast = 3;
    animationComponent.rowEast = 4;
    animationComponent.rowSouthEast = 5;
    animationComponent.rowSouth = 6;
    animationComponent.rowSouthWest = 7;

    entity.addComponent<StateComponent>();
    StateComponent& stateComponent = entity.getComponent<StateComponent>();
    stateComponent.state = "Game";

    entity.addComponent<Movable>();
    Movable& moveble = entity.getComponent<Movable>();
    moveble.speed = 10;
    moveble.path = "0";

    entity.addComponent< Looteble>();
    Looteble& looteble = entity.getComponent<Looteble>();
    looteble.gold =0;
    looteble.HealtPotion = 3;
    looteble.weapon = 10;
    looteble.armor = 10;

    entity.addComponent<HealthComponent>();
    entity.getComponent<HealthComponent>().health = 500;
    entity.getComponent<HealthComponent>().maxHealth = entity.getComponent<HealthComponent>().health;

    entity.addComponent<ActionTimer>();
    ActionTimer& actionTimer = entity.getComponent<ActionTimer>();
    actionTimer.AttackCooldown = 1.5f;
    actionTimer.PotionCooldown = 10;
    actionTimer.AttackTimer.restart().asSeconds();
    actionTimer.PotionTimer.restart().asSeconds();

    entity.addComponent<CostComponent>();
    CostComponent& costComponent = entity.getComponent<CostComponent>();
    costComponent.ArmorUpgrade = 100;
    costComponent.WeaponUpgrade= 100;

    entity.addComponent<DrawebleComponent>();

    //auto& playerCollision = entity.addComponent<CollisionComponent>();
    //playerCollision.boundingBox = sf::FloatRect(53, 76, 25, 25); // feet
    //playerCollision.causesEvents = true;

    entity.activate();
}
void SetUpCreature::setUpEnemie(anax::Entity& entity, sf::Texture& texture, sf::RenderWindow& window, int Xpos, int Ypos, std::string diffeculty)
{
    entity.addComponent<TextureComponent>();
    TextureComponent& textureComponent = entity.getComponent<TextureComponent>();
    textureComponent.texture[0] = texture;
    textureComponent.sprite[0].setTexture(texture);
    textureComponent.spriteRect.height = 128;
    textureComponent.spriteRect.width = 128;

    entity.addComponent<PositionComponent>();
    PositionComponent& positionComponent = entity.getComponent<PositionComponent>();


    positionComponent.YPos = Ypos;
    positionComponent.XPos = Xpos;
    positionComponent.SpriteLeft = Xpos + 45;
    positionComponent.SpriteTop = Ypos + 65;

    entity.addComponent<SizeComponent>();
    SizeComponent& sizeComponent = entity.getComponent<SizeComponent>();
    sizeComponent.Height = textureComponent.spriteRect.height;
    sizeComponent.Whith = textureComponent.spriteRect.width;
    sizeComponent.SpriteHeight = 34;
    sizeComponent.SpriteWhith = 32;

    entity.addComponent<AnimationComponent>();
    AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();
    animationComponent.imageCounter.x = 32;
    animationComponent.imageCounter.y = 8;
    animationComponent.switchTime = 0.08f;
    animationComponent.pixels = 128;
    animationComponent.movementSpeed = 100;
    animationComponent.row =0;
    animationComponent.currentImage.x =0;
    animationComponent.animationClock.restart().asSeconds();
    animationComponent.idleStart = 0;
    animationComponent.idleEnd = 3;
    animationComponent.walkStart = 4;
    animationComponent.walkEnd = 11;
    animationComponent.attackStart = 12;
    animationComponent.attackEnd = 15;
    animationComponent.defendStart = 16;
    animationComponent.defendEnd = 17;

    animationComponent.rowWest = 0;
    animationComponent.rowNorthWest = 1;
    animationComponent.rowNorth = 2;
    animationComponent.rowNorthEast = 3;
    animationComponent.rowEast = 4;
    animationComponent.rowSouthEast = 5;
    animationComponent.rowSouth = 6;
    animationComponent.rowSouthWest = 7;

    animationComponent.animationDirection = 0;

    entity.addComponent<StateComponent>();
    StateComponent& stateComponent = entity.getComponent<StateComponent>();
    stateComponent.state = "Game";

    entity.addComponent<Movable>();
    Movable& moveble = entity.getComponent<Movable>();


    entity.addComponent<HealthComponent>();
    HealthComponent& healthComponent = entity.getComponent<HealthComponent>();

    entity.addComponent< Looteble>();
    Looteble& looteble = entity.getComponent<Looteble>();


    entity.addComponent<DrawebleComponent>();
    entity.addComponent<MousedOver>();


    entity.addComponent<ActionTimer>();
    entity.getComponent<ActionTimer>().AttackCooldown = 1;
    entity.getComponent<ActionTimer>().AttackTimer.restart().asSeconds();

    sf::Color red(255,100,100);
    sf::Color blue(100,100,255);
    if(diffeculty == "Hard")
    {
        textureComponent.sprite[0].setColor(red);
        healthComponent.maxHealth = 100;
        moveble.speed = 7;
        looteble.gold =50 + (10*rand()%10+1);
        looteble.weapon = 50;
    }else if(diffeculty == "Medium")
    {
        textureComponent.sprite[0].setColor((blue));
        healthComponent.maxHealth = 50;
        moveble.speed = 5;
        looteble.gold =50+(5*rand()%10+1);
        looteble.weapon = 50;
    }else
    {
        healthComponent.maxHealth = 20;
        looteble.gold = rand()%10+1;
        moveble.speed = 3;
        looteble.weapon = 20;
    }
    healthComponent.health = healthComponent.maxHealth;
}
void SetUpCreature::setUpNPC(anax::Entity& entity, sf::Texture& texture, sf::RenderWindow& window, int Xpos, int Ypos, int Xofset, int Yofset)
{
    entity.addComponent<TextureComponent>();
    TextureComponent& textureComponent = entity.getComponent<TextureComponent>();
    textureComponent.texture[0] = texture;
    textureComponent.sprite[0].setTexture(texture);
    textureComponent.spriteRect.height = 64 + Xofset;
    textureComponent.spriteRect.width =  32 + 2*Yofset;
    textureComponent.sortKey = 999;

    entity.addComponent<PositionComponent>();
    PositionComponent& positionComponent = entity.getComponent<PositionComponent>();
    positionComponent.YPos = Xpos;
    positionComponent.XPos = Ypos;
    positionComponent.SpriteLeft = Xpos + Xofset;
    positionComponent.SpriteTop =  Ypos + Yofset;

    entity.addComponent<SizeComponent>();
    SizeComponent& sizeComponent = entity.getComponent<SizeComponent>();
    sizeComponent.Height = textureComponent.spriteRect.height;
    sizeComponent.Whith = textureComponent.spriteRect.width;
    sizeComponent.SpriteHeight = 64 ;
    sizeComponent.SpriteWhith =  32 ;

    entity.addComponent<AnimationComponent>();
    AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();
    animationComponent.imageCounter.x = 6;
    animationComponent.imageCounter.y = 1;
    animationComponent.switchTime = 0.2f;
    animationComponent.movementSpeed = 20;
    animationComponent.row =0;
    animationComponent.currentImage.x =0;
    animationComponent.action = "Idle";
    //animationComponent.animationClock.restart().asSeconds();

    entity.addComponent<StateComponent>();
    StateComponent& stateComponent = entity.getComponent<StateComponent>();
    stateComponent.state = "Game";

    entity.addComponent<MousedOver>();

    entity.addComponent<Looteble>();
    Looteble& looteble = entity.getComponent<Looteble>();
    looteble.gold = 0;

    entity.addComponent<Talkative>();
    entity.addComponent<ChildComponent>();
    entity.addComponent<DrawebleComponent>();



    entity.activate();
}

void SetUpCreature::setUpBoss(anax::Entity& entity, sf::Texture& texture, sf::RenderWindow& window, int Xpos, int Ypos)
{

    entity.addComponent<TextureComponent>();
    TextureComponent& textureComponent = entity.getComponent<TextureComponent>();
    textureComponent.texture[0] = texture;
    textureComponent.sprite[0].setTexture(texture);
    textureComponent.spriteRect.height = 128;
    textureComponent.spriteRect.width = 128;

    entity.addComponent<PositionComponent>();
    PositionComponent& positionComponent = entity.getComponent<PositionComponent>();


    positionComponent.YPos = Ypos;
    positionComponent.XPos = Xpos;
    positionComponent.SpriteLeft = Xpos + 45;
    positionComponent.SpriteTop = Ypos + 65;

    entity.addComponent<SizeComponent>();
    SizeComponent& sizeComponent = entity.getComponent<SizeComponent>();
    sizeComponent.Height = textureComponent.spriteRect.height;
    sizeComponent.Whith = textureComponent.spriteRect.width;
    sizeComponent.SpriteHeight = 34;
    sizeComponent.SpriteWhith = 32;

    entity.addComponent<AnimationComponent>();
    AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();
    animationComponent.imageCounter.x = 32;
    animationComponent.imageCounter.y = 8;
    animationComponent.switchTime = 0.08f;
    animationComponent.pixels = 128;
    animationComponent.movementSpeed = 100;
    animationComponent.row =0;
    animationComponent.currentImage.x =0;
    animationComponent.animationClock.restart().asSeconds();
    animationComponent.idleStart = 0;
    animationComponent.idleEnd = 3;
    animationComponent.walkStart = 4;
    animationComponent.walkEnd = 11;
    animationComponent.attackStart = 12;
    animationComponent.attackEnd = 15;
    animationComponent.defendStart = 16;
    animationComponent.defendEnd = 17;

    animationComponent.rowWest = 0;
    animationComponent.rowNorthWest = 1;
    animationComponent.rowNorth = 2;
    animationComponent.rowNorthEast = 3;
    animationComponent.rowEast = 4;
    animationComponent.rowSouthEast = 5;
    animationComponent.rowSouth = 6;
    animationComponent.rowSouthWest = 7;

    animationComponent.animationDirection = 0;

    entity.addComponent<StateComponent>();
    StateComponent& stateComponent = entity.getComponent<StateComponent>();
    stateComponent.state = "Game";

    entity.addComponent<Movable>();
    Movable& moveble = entity.getComponent<Movable>();


    entity.addComponent<HealthComponent>();
    HealthComponent& healthComponent = entity.getComponent<HealthComponent>();

    entity.addComponent< Looteble>();
    Looteble& looteble = entity.getComponent<Looteble>();
    looteble.weapon = 50;


    entity.addComponent<DrawebleComponent>();
    entity.addComponent<MousedOver>();


    entity.addComponent<ActionTimer>();
    entity.getComponent<ActionTimer>().AttackCooldown = 5;
    entity.getComponent<ActionTimer>().AttackTimer.restart().asSeconds();


    sf::Color black(100,100,100);
    textureComponent.sprite[0].setColor(black);
    textureComponent.sprite[0].setScale(1.5,1.5);
    healthComponent.maxHealth = 100;
    moveble.speed = 10;
    looteble.gold =50 + (10*rand()%10+1);
    looteble.weapon = 30;
    healthComponent.health = healthComponent.maxHealth;
}
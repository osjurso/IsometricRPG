#include <components/Comp_Texture.h>
#include <systems/drawEntety.h>
#include <collections/setUpCreature.h>
#include <collections/addDialogue.h>
#include <collections/addDialogueOption.h>
#include <collections/mouseClickedFunctions.h>
#include <components/CompCost.h>
#include "collections/setUpAllCreatures.h"


setUpAllCreatures::setUpAllCreatures(StateBase::Context context) :context(context)
{}

void setUpAllCreatures::SetUpCreatures(anax::Entity& player, bool createPlayer)
{
    sf::Texture& GoblinTexture = context.textures->get(Textures::Goblin);
    sf::Texture& TraderTexture = context.textures->get(Textures::Trader);
    sf::Texture& ArmorerTexture = context.textures->get(Textures::Armorer);

    if (createPlayer)
    {
        sf::Texture& HeroBody = context.textures->get(Textures::Hero);
        sf::Texture& HeroHead = context.textures->get(Textures::HeroHead);
        sf::Texture& HeroWeapon = context.textures->get(Textures::HeroWeapon);
        sf::Texture& HeroShield = context.textures->get(Textures::HeroShield);

        player.addComponent<TextureComponent>();
        TextureComponent& textureComponent = player.getComponent<TextureComponent>();
        textureComponent.texture[0] = HeroBody;
        textureComponent.sprite[0].setTexture(textureComponent.texture[0]);
        textureComponent.texture[1] = HeroHead;
        textureComponent.sprite[1].setTexture(textureComponent.texture[1]);
        textureComponent.texture[2] = HeroWeapon;
        textureComponent.sprite[2].setTexture(textureComponent.texture[2]);
        textureComponent.texture[3] = HeroShield;
        textureComponent.sprite[3].setTexture(textureComponent.texture[3]);
    }

    sf::RenderWindow& window = *context.window;
    DrawEntetys drawEntetys;

    anax::World& world = *context.world;

    //anax::Entity goblin = world.createEntity();
    //anax::Entity goblin2 = world.createEntity();
    //anax::Entity goblin3 = world.createEntity();
    //anax::Entity goblin4 = world.createEntity();
    anax::Entity trader = world.createEntity();
    anax::Entity armorer = world.createEntity();
    //anax::Entity boss = world.createEntity();

    SetUpCreature creatureSetup;

    if (createPlayer)
        creatureSetup.setUpPlayer(player, window);

    //creatureSetup.setUpEnemies(goblin,  GoblinTexture, window, 200, 200, "Hard");
    //creatureSetup.setUpEnemies(goblin2, GoblinTexture, window ,100 ,100, "Medium");
    //creatureSetup.setUpEnemies(goblin3, GoblinTexture, window ,400 ,200, "Easy");
    //creatureSetup.setUpEnemies(goblin4, GoblinTexture, window ,300 ,100, "Hard");
    //creatureSetup.setUpBoss(boss,GoblinTexture,window,200,200);

    creatureSetup.setUpNPC(trader,TraderTexture  ,window,62,1060,0,0);
    creatureSetup.setUpNPC(armorer,ArmorerTexture,window,350,350,42,42);

    trader.getComponent<PositionComponent>().XPos = 152;
    trader.getComponent<PositionComponent>().SpriteLeft = trader.getComponent<PositionComponent>().XPos;
    trader.getComponent<PositionComponent>().YPos = 1110;
    trader.getComponent<PositionComponent>().SpriteTop = trader.getComponent<PositionComponent>().YPos;

    armorer.getComponent<PositionComponent>().XPos = 680;
    armorer.getComponent<PositionComponent>().SpriteLeft = armorer.getComponent<PositionComponent>().XPos + 42;
    armorer.getComponent<PositionComponent>().YPos = 700;
    armorer.getComponent<PositionComponent>().SpriteTop = armorer.getComponent<PositionComponent>().YPos +42;

    trader.getComponent<TextureComponent>().sortKey = trader.getComponent<PositionComponent>().SpriteTop + 60;
    armorer.getComponent<TextureComponent>().sortKey = armorer.getComponent<PositionComponent>().SpriteTop + 60;

    AddDialogue addDialogue;
    AddOptionDialogue optionDialogue;

    addDialogue.addDialogue(trader, "assets/dialog/trader_dialog_0.txt", 0);
    trader.getComponent<Talkative>().TotalOfDialogs += 1;

    addDialogue.addDialogue(trader, "assets/dialog/trader_dialog_1.txt", 1);
    optionDialogue.addOptionDialogue(trader, "Buy health potion  50g", 1, 3, BuyHealthPotion);
    optionDialogue.addOptionDialogue(trader, "What's my purpose here again?", 1, 4, setInfo);
    optionDialogue.addOptionDialogue(trader, "Punch me, I dare you!", 1, 5, healthPunishment);
    trader.getComponent<Talkative>().TotalOfDialogs += 1;

    trader.getComponent<Talkative>().Default = 1;
    trader.getComponent<Talkative>().Current = 0;

    addDialogue.addDialogue(armorer, "assets/dialog/armorer_dialog_0.txt", 0);
    armorer.getComponent<Talkative>().TotalOfDialogs +=1;

    addDialogue.addDialogue(armorer, "assets/dialog/armorer_dialog_1.txt", 1);
    optionDialogue.addOptionDialogue(armorer, "Upgrade Armor " +
                                             std::to_string(player.getComponent<CostComponent>().ArmorUpgrade) + "g", 1,
                                    3, BuyArmorUpgrade);
    optionDialogue.addOptionDialogue(armorer, "Upgrade Weapon " +
                                             std::to_string(player.getComponent<CostComponent>().WeaponUpgrade) + "g",
                                    1, 4, BuyWeaponUpgrade);
    optionDialogue.addOptionDialogue(armorer, "Pay me for my kills", 1, 5, PayUp);
    armorer.getComponent<Talkative>().TotalOfDialogs +=1;

    armorer.getComponent<Talkative>().Default = 1;
    armorer.getComponent<Talkative>().Current = 0;
}
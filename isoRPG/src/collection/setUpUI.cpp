#include <collections/setUpUI.h>
#include <include/collections/setUpRectShape.h>
#include <include/components/Comp_SqureShape.h>
#include <include/components/Comp_Changeble.h>

void SetUpUI::setUpUI(anax::World &world, float zoom, sf::Texture& bottomTexture, sf::Texture& itemTexture, sf::Texture& abilitiesTexture, sf::Texture& healtBarTexture, sf::Texture& transparant, sf::Font font, sf::View playerCam, anax::Entity player)
{

    //sets up background
    anax::Entity bottom = world.createEntity();
    anax::Entity items = world.createEntity();
    anax::Entity abilities = world.createEntity();
    anax::Entity healtbar = world.createEntity();

    anax::Entity attackCooldown = world.createEntity();
    anax::Entity defendCooldown = world.createEntity();
    anax::Entity healtCooldown = world.createEntity();



    bottom.addComponent<UIComp>();
    items.addComponent<UIComp>();
    abilities.addComponent<UIComp>();
    healtbar.addComponent<UIComp>();

    bottom.getComponent<UIComp>().Yofset = -60;

    items.getComponent<UIComp>().Yofset = -50;
    items.getComponent<UIComp>().Xofset = 400;

    abilities.getComponent<UIComp>().Yofset = -25;
    abilities.getComponent<UIComp>().Xofset = 40;

    healtbar.getComponent<UIComp>().Yofset = -55;
    healtbar.getComponent<UIComp>().Xofset = 30;

    Draweble draweble;
    draweble.makeDraweble(itemTexture,0, 0, items,"Game");
    items.getComponent<TextureComponent>().sprite->setScale(zoom,zoom);

    draweble.makeDraweble(bottomTexture,0,0, bottom,"Game");
    bottom.getComponent<TextureComponent>().sprite->setScale(zoom,zoom);

    draweble.makeDraweble(abilitiesTexture,0,0,abilities,"Game");
    abilities.getComponent<TextureComponent>().sprite->setScale(zoom/1.5,zoom/1.5);

    draweble.makeDraweble(healtBarTexture,0,0,healtbar,"Game");
    healtbar.getComponent<TextureComponent>().sprite->setScale(zoom/2,zoom/2);


    bottom.getComponent<TextureComponent>().sortKey = 5000;
    items.getComponent<TextureComponent>().sortKey = 5001;
    abilities.getComponent<TextureComponent>().sortKey = 5002;
    healtbar.getComponent<TextureComponent>().sortKey = 5005;

    //set up timers
    draweble.makeDraweble(transparant,0,0,attackCooldown,"Game");
    draweble.makeDraweble(transparant,0,0,defendCooldown,"Game");
    draweble.makeDraweble(transparant,0,0,healtCooldown,"Game");

    attackCooldown.getComponent<TextureComponent>().sprite->setScale(zoom/1.2,zoom/1.2);
    defendCooldown.getComponent<TextureComponent>().sprite->setScale(zoom/1.2,zoom/1.2);
    healtCooldown.getComponent<TextureComponent>().sprite->setScale(zoom/1.2,zoom/1.2);

    attackCooldown.getComponent<TextureComponent>().sortKey = 5007;
    defendCooldown.getComponent<TextureComponent>().sortKey = 5007;
    healtCooldown.getComponent<TextureComponent>().sortKey = 5007;

    attackCooldown.addComponent<UIComp>();
    attackCooldown.getComponent<UIComp>().Xofset = 42;
    attackCooldown.getComponent<UIComp>().Yofset = -23;

    defendCooldown.addComponent<UIComp>();
    defendCooldown.getComponent<UIComp>().Xofset = 74;
    defendCooldown.getComponent<UIComp>().Yofset = -23;

    healtCooldown.addComponent<UIComp>();
    healtCooldown.getComponent<UIComp>().Xofset = 106;
    healtCooldown.getComponent<UIComp>().Yofset = -23;

    attackCooldown.addComponent<ChangebleComponent>();
    defendCooldown.addComponent<ChangebleComponent>();
    healtCooldown.addComponent<ChangebleComponent>();
    attackCooldown.getComponent<ChangebleComponent>().source = "Attack";
    defendCooldown.getComponent<ChangebleComponent>().source = "Defend";
    healtCooldown.getComponent<ChangebleComponent>().source = "Potion";

    //sets up text

    sf::Color gold(255,215,0);
    sf::Color steel(67, 70, 75);
    sf::Color potionRed(230, 0, 27);
    sf::Color magicPurple(102, 51, 153);

    anax::Entity HPotionCount = world.createEntity();
    anax::Entity GoldCount = world.createEntity();
    anax::Entity ArmorModifierCount = world.createEntity();
    anax::Entity WeaponModifierCount = world.createEntity();
    anax::Entity ArmorBase = world.createEntity();
    anax::Entity WeaponBase = world.createEntity();

    DrawebleText drawebleText;
    std::string nrPotion = " x "+ std::to_string(player.getComponent<Looteble>().HealtPotion);
    std::string nrGold   = " x "+ std::to_string(player.getComponent<Looteble>().gold);
    std::string ModArmor = " + "+ std::to_string(player.getComponent<Looteble>().armorModifier);
    std::string ModSword = " + "+ std::to_string(player.getComponent<Looteble>().weaponModifier);
    std::string Armor    =  " " + std::to_string(player.getComponent<Looteble>().armor);
    std::string Weapon   =  " " + std::to_string(player.getComponent<Looteble>().weapon);

    drawebleText.setUpDrawebleText(HPotionCount ,nrPotion, playerCam, "Game", zoom,font,potionRed);
    drawebleText.setUpDrawebleText(GoldCount    ,nrGold  , playerCam, "Game", zoom,font,gold);

    drawebleText.setUpDrawebleText(ArmorModifierCount  ,ModArmor, playerCam, "Game", zoom,font,magicPurple);
    drawebleText.setUpDrawebleText(WeaponModifierCount ,ModSword, playerCam, "Game", zoom,font,magicPurple);
    drawebleText.setUpDrawebleText(WeaponBase          ,Weapon,   playerCam, "Game", zoom,font,steel);
    drawebleText.setUpDrawebleText(ArmorBase           ,Armor,    playerCam, "Game", zoom,font,steel);

    HPotionCount.getComponent<UIComp>().Xofset = 425;
    HPotionCount.getComponent<UIComp>().Yofset = -45;
    HPotionCount.getComponent<TextComponent>().content = "Potion";
    HPotionCount.getComponent<TextureComponent>().sortKey = 5020;

    GoldCount.getComponent<UIComp>().Xofset = 425;
    GoldCount.getComponent<UIComp>().Yofset = -20;
    GoldCount.getComponent<TextComponent>().content = "Gold";
    GoldCount.getComponent<TextureComponent>().sortKey = 5020;


    ArmorBase.getComponent<UIComp>().Xofset = 500;
    ArmorBase.getComponent<UIComp>().Yofset = -20;
    ArmorBase.getComponent<TextComponent>().content = "ArmorBase";
    ArmorBase.getComponent<TextureComponent>().sortKey = 5020;

    ArmorModifierCount.getComponent<UIComp>().Xofset = 540;
    ArmorModifierCount.getComponent<UIComp>().Yofset = -20;
    ArmorModifierCount.getComponent<TextComponent>().content = "ArmorMod";
    ArmorModifierCount.getComponent<TextureComponent>().sortKey = 5020;


    WeaponBase.getComponent<UIComp>().Xofset = 500;
    WeaponBase.getComponent<UIComp>().Yofset = -45;
    WeaponBase.getComponent<TextComponent>().content = "WeaponBase";
    WeaponBase.getComponent<TextureComponent>().sortKey = 5020;

    WeaponModifierCount.getComponent<UIComp>().Xofset = 540;
    WeaponModifierCount.getComponent<UIComp>().Yofset = -45;
    WeaponModifierCount.getComponent<TextComponent>().content = "WeaponMod";
    WeaponModifierCount.getComponent<TextureComponent>().sortKey = 5020;

    anax::Entity attackText = world.createEntity();
    anax::Entity defendText= world.createEntity();
    anax::Entity HealText = world.createEntity();

    std::string attackKey = "Spacebar";
    std::string defendKey = "Shift";
    std::string healKey = "Q";

    drawebleText.setUpDrawebleText(attackText ,attackKey, playerCam, "Game", zoom,font,steel);
    drawebleText.setUpDrawebleText(defendText ,defendKey, playerCam, "Game", zoom,font,steel);
    drawebleText.setUpDrawebleText(HealText   ,healKey,   playerCam, "Game", zoom,font,steel);

    attackText.getComponent<UIComp>().Xofset = 35;
    attackText.getComponent<UIComp>().Yofset = -40;

    defendText.getComponent<UIComp>().Xofset = 75;
    defendText.getComponent<UIComp>().Yofset = -40;

    HealText.getComponent<UIComp>().Xofset = 113;
    HealText.getComponent<UIComp>().Yofset = -40;


    //sets up healtbar
    anax::Entity healtTotal = world.createEntity();
    anax::Entity healtCurrnet = world.createEntity();

    SetUpRectShape setUpRectShape;

    setUpRectShape.setUpRectshape(healtTotal,100,100,110,9,zoom,sf::Color(100,10,10), playerCam);
    setUpRectShape.setUpRectshape(healtCurrnet,100,100,110,9,zoom,sf::Color(165,10,10), playerCam);

    healtCurrnet.getComponent<TextureComponent>().sortKey = 5004;
    healtTotal.getComponent<TextureComponent>().sortKey = 5003;

    healtTotal.addComponent<UIComp>();
    healtCurrnet.addComponent<UIComp>();
    healtTotal.getComponent<UIComp>().Xofset = 32;
    healtTotal.getComponent<UIComp>().Yofset = -52;

    healtCurrnet.getComponent<UIComp>().Xofset = 32;
    healtCurrnet.getComponent<UIComp>().Yofset = -52;

    healtCurrnet.addComponent<ChangebleComponent>();
}





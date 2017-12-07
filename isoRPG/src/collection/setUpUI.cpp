#include <collections/setUpUI.h>
#include <include/collections/setUpHealt.h>
#include <include/components/Comp_SqureShape.h>

void SetUpUI::setUpUI(anax::World &world, float zoom, sf::Texture& bottomTexture, sf::Texture& itemTexture, sf::Texture& abilitiesTexture, sf::Texture& healtBarTexture, sf::Font font, sf::View playerCam, anax::Entity player)
{

    //sets up background
    anax::Entity bottom = world.createEntity();
    anax::Entity items = world.createEntity();
    anax::Entity abilities = world.createEntity();
    anax::Entity healtbar = world.createEntity();


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


    bottom.getComponent<TextureComponent>().sortKey = 1000;
    items.getComponent<TextureComponent>().sortKey = 1001;
    abilities.getComponent<TextureComponent>().sortKey = 1002;
    healtbar.getComponent<TextureComponent>().sortKey = 1005;


    //sets up text

    sf::Color gold(255,215,0);
    sf::Color steel(67, 70, 75);
    sf::Color potionRed(230, 0, 27);

    anax::Entity HPotionCount = world.createEntity();
    anax::Entity GoldCount = world.createEntity();
    anax::Entity ArmorCount = world.createEntity();
    anax::Entity WeaponCount = world.createEntity();

    anax::Entity attackText = world.createEntity();
    anax::Entity defendText= world.createEntity();
    anax::Entity HealText = world.createEntity();

    DrawebleText drawebleText;
    std::string nrPotion = "x "+ std::to_string(3);
    std::string nrGold = "x "+ std::to_string(player.getComponent<Looteble>().gold);
    std::string nrArmor = "10 + "+ std::to_string(0);
    std::string nrSword = "10 + "+ std::to_string(0);

    std::string attackKey = "Spacebar";
    std::string defendKey = "Shift";
    std::string healKey = "Q";


    drawebleText.setUpDrawebleText(HPotionCount ,nrPotion, playerCam, "Game", zoom,font,potionRed);
    drawebleText.setUpDrawebleText(GoldCount ,nrGold, playerCam, "Game", zoom,font,gold);
    drawebleText.setUpDrawebleText(ArmorCount ,nrArmor, playerCam, "Game", zoom,font,steel);
    drawebleText.setUpDrawebleText(WeaponCount ,nrSword, playerCam, "Game", zoom,font,steel);

    drawebleText.setUpDrawebleText(attackText ,attackKey, playerCam, "Game", zoom,font,steel);
    drawebleText.setUpDrawebleText(defendText ,defendKey, playerCam, "Game", zoom,font,steel);
    drawebleText.setUpDrawebleText(HealText ,healKey, playerCam, "Game", zoom,font,steel);

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


    attackText.getComponent<UIComp>().Xofset = 35;
    attackText.getComponent<UIComp>().Yofset = -40;

    defendText.getComponent<UIComp>().Xofset = 75;
    defendText.getComponent<UIComp>().Yofset = -40;

    HealText.getComponent<UIComp>().Xofset = 113;
    HealText.getComponent<UIComp>().Yofset = -40;


    //sets up healtbar
    anax::Entity healtTotal = world.createEntity();
    anax::Entity healtCurrnet = world.createEntity();

    SetUpHealt setUpHealt;
    setUpHealt.setUpHealt(healtTotal,100,100,110,9,zoom,sf::Color(100,10,10), playerCam);
    setUpHealt.setUpHealt(healtCurrnet,100,100,110,9,zoom,sf::Color(165,10,10), playerCam);

    healtCurrnet.getComponent<SqureComponent>().changeble = true;
    healtCurrnet.getComponent<TextureComponent>().sortKey = 1004;
    healtTotal.getComponent<TextureComponent>().sortKey = 1003;

    healtTotal.addComponent<UIComp>();
    healtCurrnet.addComponent<UIComp>();
    healtTotal.getComponent<UIComp>().Xofset = 32;
    healtTotal.getComponent<UIComp>().Yofset = -52;

    healtCurrnet.getComponent<UIComp>().Xofset = 32;
    healtCurrnet.getComponent<UIComp>().Yofset = -52;
}





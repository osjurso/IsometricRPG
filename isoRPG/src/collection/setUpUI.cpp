#include <collections/setUpUI.h>

void SetUpUI::setUpUI(anax::World &world, float zoom, sf::Texture& bottomTexture, sf::Texture& itemTexture, sf::Font font, sf::View playerCam, anax::Entity player)
{
    anax::Entity bottom = world.createEntity();
    anax::Entity items = world.createEntity();

    bottom.addComponent<UIComp>();
    items.addComponent<UIComp>();

    bottom.getComponent<UIComp>().Yofset = -60;
    items.getComponent<UIComp>().Yofset = -50;
    items.getComponent<UIComp>().Xofset = 400;

    Draweble draweble;
    draweble.makeDraweble(itemTexture,0, 0, items,"Game");
    items.getComponent<TextureComponent>().sprite->setScale(zoom,zoom);

    draweble.makeDraweble(bottomTexture,0,0, bottom,"Game");
    bottom.getComponent<TextureComponent>().sprite->setScale(zoom,zoom);

    bottom.getComponent<TextureComponent>().sortKey = 1000;
    items.getComponent<TextureComponent>().sortKey = 1001;

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
}





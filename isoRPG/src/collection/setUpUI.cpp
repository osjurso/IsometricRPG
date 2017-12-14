#include <collections/setUpUI.h>
#include <collections/setUpRectShape.h>
#include <components/Comp_Changeable.h>

void SetUpUI::setUpUI(anax::World &world, float zoom, sf::Texture& bottomTexture, sf::Texture& itemTexture, sf::Texture& abilitiesTexture, sf::Texture& healthBar, sf::Texture& transperant, sf::Font font, sf::View playerCam, anax::Entity player)
{

    //sets up background
    anax::Entity bottom = world.createEntity();
    anax::Entity items = world.createEntity();
    anax::Entity abilities = world.createEntity();
    anax::Entity healtbar = world.createEntity();

    anax::Entity attackCooldown = world.createEntity();
    anax::Entity defendCooldown = world.createEntity();
    anax::Entity healthCooldown = world.createEntity();



    bottom.addComponent<UIComp>();
    items.addComponent<UIComp>();
    abilities.addComponent<UIComp>();
    healtbar.addComponent<UIComp>();

    bottom.getComponent<UIComp>().yOffset = -60;

    items.getComponent<UIComp>().yOffset = -50;
    items.getComponent<UIComp>().xOffset = 400;

    abilities.getComponent<UIComp>().yOffset = -25;
    abilities.getComponent<UIComp>().xOffset = 40;

    healtbar.getComponent<UIComp>().yOffset = -55;
    healtbar.getComponent<UIComp>().xOffset = 30;

    Drawable draweble;
    draweble.makeDrawable(itemTexture, 0, 0, items, "Game");
    items.getComponent<TextureComponent>().sprite->setScale(zoom,zoom);

    draweble.makeDrawable(bottomTexture, 0, 0, bottom, "Game");
    bottom.getComponent<TextureComponent>().sprite->setScale(zoom,zoom);

    draweble.makeDrawable(abilitiesTexture, 0, 0, abilities, "Game");
    abilities.getComponent<TextureComponent>().sprite->setScale(zoom/1.5,zoom/1.5);

    draweble.makeDrawable(healthBar, 0, 0, healtbar, "Game");
    healtbar.getComponent<TextureComponent>().sprite->setScale(zoom/2,zoom/2);


    bottom.getComponent<TextureComponent>().sortKey = 5000;
    items.getComponent<TextureComponent>().sortKey = 5001;
    abilities.getComponent<TextureComponent>().sortKey = 5002;
    healtbar.getComponent<TextureComponent>().sortKey = 5005;

    //set up timers
    draweble.makeDrawable(transperant, 0, 0, attackCooldown, "Game");
    draweble.makeDrawable(transperant, 0, 0, defendCooldown, "Game");
    draweble.makeDrawable(transperant, 0, 0, healthCooldown, "Game");

    attackCooldown.getComponent<TextureComponent>().sprite->setScale(zoom/1.2,zoom/1.2);
    defendCooldown.getComponent<TextureComponent>().sprite->setScale(zoom/1.2,zoom/1.2);
    healthCooldown.getComponent<TextureComponent>().sprite->setScale(zoom/1.2,zoom/1.2);

    attackCooldown.getComponent<TextureComponent>().sortKey = 5007;
    defendCooldown.getComponent<TextureComponent>().sortKey = 5007;
    healthCooldown.getComponent<TextureComponent>().sortKey = 5007;

    attackCooldown.addComponent<UIComp>();
    attackCooldown.getComponent<UIComp>().xOffset = 42;
    attackCooldown.getComponent<UIComp>().yOffset = -23;

    defendCooldown.addComponent<UIComp>();
    defendCooldown.getComponent<UIComp>().xOffset = 74;
    defendCooldown.getComponent<UIComp>().yOffset = -23;

    healthCooldown.addComponent<UIComp>();
    healthCooldown.getComponent<UIComp>().xOffset = 106;
    healthCooldown.getComponent<UIComp>().yOffset = -23;

    attackCooldown.addComponent<ChangeableComponent>();
    defendCooldown.addComponent<ChangeableComponent>();
    healthCooldown.addComponent<ChangeableComponent>();
    attackCooldown.getComponent<ChangeableComponent>().source = "Attack";
    defendCooldown.getComponent<ChangeableComponent>().source = "Defend";
    healthCooldown.getComponent<ChangeableComponent>().source = "Potion";

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

    DrawableText drawebleText;
    std::string nrPotion = " x "+ std::to_string(player.getComponent<Lootable>().HealthPotion);
    std::string nrGold   = " x "+ std::to_string(player.getComponent<Lootable>().gold);
    std::string ModArmor = " + "+ std::to_string(player.getComponent<Lootable>().armorModifier);
    std::string ModSword = " + "+ std::to_string(player.getComponent<Lootable>().weaponModifier);
    std::string Armor    =  " " + std::to_string(player.getComponent<Lootable>().armor);
    std::string Weapon   =  " " + std::to_string(player.getComponent<Lootable>().weapon);

    drawebleText.setUpDrawableText(HPotionCount, nrPotion, playerCam, "Game", zoom, font, potionRed);
    drawebleText.setUpDrawableText(GoldCount, nrGold, playerCam, "Game", zoom, font, gold);

    drawebleText.setUpDrawableText(ArmorModifierCount, ModArmor, playerCam, "Game", zoom, font, magicPurple);
    drawebleText.setUpDrawableText(WeaponModifierCount, ModSword, playerCam, "Game", zoom, font, magicPurple);
    drawebleText.setUpDrawableText(WeaponBase, Weapon, playerCam, "Game", zoom, font, steel);
    drawebleText.setUpDrawableText(ArmorBase, Armor, playerCam, "Game", zoom, font, steel);

    HPotionCount.getComponent<UIComp>().xOffset = 425;
    HPotionCount.getComponent<UIComp>().yOffset = -45;
    HPotionCount.getComponent<TextComponent>().content = "Potion";
    HPotionCount.getComponent<TextureComponent>().sortKey = 5020;

    GoldCount.getComponent<UIComp>().xOffset = 425;
    GoldCount.getComponent<UIComp>().yOffset = -20;
    GoldCount.getComponent<TextComponent>().content = "Gold";
    GoldCount.getComponent<TextureComponent>().sortKey = 5020;


    ArmorBase.getComponent<UIComp>().xOffset = 500;
    ArmorBase.getComponent<UIComp>().yOffset = -20;
    ArmorBase.getComponent<TextComponent>().content = "ArmorBase";
    ArmorBase.getComponent<TextureComponent>().sortKey = 5020;

    ArmorModifierCount.getComponent<UIComp>().xOffset = 540;
    ArmorModifierCount.getComponent<UIComp>().yOffset = -20;
    ArmorModifierCount.getComponent<TextComponent>().content = "ArmorMod";
    ArmorModifierCount.getComponent<TextureComponent>().sortKey = 5020;


    WeaponBase.getComponent<UIComp>().xOffset = 500;
    WeaponBase.getComponent<UIComp>().yOffset = -45;
    WeaponBase.getComponent<TextComponent>().content = "WeaponBase";
    WeaponBase.getComponent<TextureComponent>().sortKey = 5020;

    WeaponModifierCount.getComponent<UIComp>().xOffset = 540;
    WeaponModifierCount.getComponent<UIComp>().yOffset = -45;
    WeaponModifierCount.getComponent<TextComponent>().content = "WeaponMod";
    WeaponModifierCount.getComponent<TextureComponent>().sortKey = 5020;

    anax::Entity attackText = world.createEntity();
    anax::Entity defendText= world.createEntity();
    anax::Entity HealText = world.createEntity();

    std::string attackKey = "Spacebar";
    std::string defendKey = "Shift";
    std::string healKey = "Q";

    drawebleText.setUpDrawableText(attackText, attackKey, playerCam, "Game", zoom, font, steel);
    drawebleText.setUpDrawableText(defendText, defendKey, playerCam, "Game", zoom, font, steel);
    drawebleText.setUpDrawableText(HealText, healKey, playerCam, "Game", zoom, font, steel);



    attackText.getComponent<UIComp>().xOffset = 35;
    attackText.getComponent<UIComp>().yOffset = -40;
    attackText.getComponent<TextureComponent>().sortKey = 5020;

    defendText.getComponent<UIComp>().xOffset = 75;
    defendText.getComponent<UIComp>().yOffset = -40;
    defendText.getComponent<TextureComponent>().sortKey = 5020;

    HealText.getComponent<UIComp>().xOffset = 113;
    HealText.getComponent<UIComp>().yOffset = -40;
    HealText.getComponent<TextureComponent>().sortKey = 5020;


    //sets up healtbar
    anax::Entity healthTotal = world.createEntity();
    anax::Entity healthCurrent = world.createEntity();

    SetUpRectShape setUpRectShape;

    setUpRectShape.setUpRectShape(healthTotal, 100, 100, 110, 9, zoom, sf::Color(100, 10, 10), playerCam);
    setUpRectShape.setUpRectShape(healthCurrent, 100, 100, 110, 9, zoom, sf::Color(165, 10, 10), playerCam);

    healthCurrent.getComponent<TextureComponent>().sortKey = 5004;
    healthTotal.getComponent<TextureComponent>().sortKey = 5003;

    healthTotal.addComponent<UIComp>();
    healthCurrent.addComponent<UIComp>();
    healthTotal.getComponent<UIComp>().xOffset = 32;
    healthTotal.getComponent<UIComp>().yOffset = -52;

    healthCurrent.getComponent<UIComp>().xOffset = 32;
    healthCurrent.getComponent<UIComp>().yOffset = -52;

    healthCurrent.addComponent<ChangeableComponent>();
}





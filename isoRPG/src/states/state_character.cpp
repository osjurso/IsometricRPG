#include <include/collections/drawable.h>
#include <include/systems/drawEntety.h>
#include <fstream>
#include <include/collections/drawebleText.h>
#include <include/components/Comp_AssosiateFunc.h>
#include <include/collections/mouseClikedFunctions.h>
#include <include/components/Comp_Menuchoice.h>
#include "include/states/state_character.h"
#include "include/gameEngine/resource_holder.h"

StateCharacter::StateCharacter(StateStack &stack, Context context)
        : StateBase(stack, context)
{
    sf::Font& font = context.fonts->get(Fonts::RPG);

    anax::World& world = *getContext().world;
    sf::RenderWindow& window = *getContext().window;


    anax::Entity background = world.createEntity();

    anax::Entity saveSlot1 = world.createEntity();
    anax::Entity saveSlot2 = world.createEntity();
    anax::Entity saveSlot3 = world.createEntity();

    Draweble draweble;

    draweble.makeDraweble(context.textures->get(Textures::SettingsBackdorp),0,0,background,"Character");

    float boxoffset = 300;
    draweble.makeDraweble(context.textures->get(Textures::CharacterBox),500,80,saveSlot1,"Character");
    draweble.makeDraweble(context.textures->get(Textures::CharacterBox),500,80 + boxoffset,saveSlot2,"Character");
    draweble.makeDraweble(context.textures->get(Textures::CharacterBox),500,80 + boxoffset*2,saveSlot3,"Character");

    background.getComponent<TextureComponent>().sortKey = 10;

    saveSlot1.getComponent<TextureComponent>().sortKey = 11;
    saveSlot2.getComponent<TextureComponent>().sortKey = 11;
    saveSlot3.getComponent<TextureComponent>().sortKey = 11;

    //read form file
    // 1. Name
    // 2. Gold
    // 3: Healt potion
    // 4. Armor
    // 5. Armor mod
    // 6. Weapon
    // 7. Weapon mod

    std::ifstream file1("assets/saves/save1.txt");
    std::ifstream file2("assets/saves/save2.txt");
    std::ifstream file3("assets/saves/save3.txt");

    std::string tempstring;

    int nr = 0;
    firstFull = false;
    std::map<int,std::string> file1Text;
    secondFull = false;
    std::map<int,std::string> file2Text;
    thirdFull = false;
    std::map<int,std::string> file3Text;


    while (std::getline(file1, tempstring))
    {
        file1Text[nr] = tempstring;
        nr++;
    }
    if(nr > 0) firstFull = true;
    nr = 0;
    while (std::getline(file2, tempstring))
    {
        file2Text[nr] = tempstring;
        nr++;
    }
    if(nr > 0) secondFull = true;
    nr = 0;
    while (std::getline(file3, tempstring))
    {
        file3Text[nr] = tempstring;
        nr++;
    }
    if(nr > 0) thirdFull = true;

    DrawebleText drawebleText;
    sf::View cam= window.getView();

    anax::Entity createNew1 = world.createEntity();
    draweble.makeDraweble(getContext().textures->get(Textures::CharacterNew),850,250,createNew1,"Character");
    createNew1.getComponent<TextureComponent>().sortKey = 12;
    createNew1.addComponent<MousedOver>();
    createNew1.addComponent<AssosateFunc>();
    createNew1.addComponent<MenuChoiceComponent>();

    if(firstFull)
    {
        anax::Entity player1Name = world.createEntity();
        anax::Entity player1Gold = world.createEntity();
        anax::Entity player1HeathPotion = world.createEntity();
        anax::Entity player1Armor = world.createEntity();
        anax::Entity player1ArmorMod = world.createEntity();
        anax::Entity player1Weapon = world.createEntity();
        anax::Entity player1WeaponMod = world.createEntity();

        drawebleText.setUpDrawebleText(player1Name,               "Name: " + file1Text.at(0),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player1Gold,               "Gold: " + file1Text.at(1),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player1HeathPotion,"Healt potion: " + file1Text.at(2),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player1Armor,             "Armor: " + file1Text.at(3),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player1ArmorMod,              " + " + file1Text.at(4),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player1Weapon,           "Weapon: " + file1Text.at(5),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player1WeaponMod,             " + " + file1Text.at(6),cam,"Character",1,font,sf::Color().Black);

        player1Name.getComponent<TextureComponent>().sortKey = 13;
        player1Gold.getComponent<TextureComponent>().sortKey = 13;
        player1HeathPotion.getComponent<TextureComponent>().sortKey = 13;
        player1Armor.getComponent<TextureComponent>().sortKey = 13;
        player1ArmorMod.getComponent<TextureComponent>().sortKey = 13;
        player1Weapon.getComponent<TextureComponent>().sortKey = 13;
        player1WeaponMod.getComponent<TextureComponent>().sortKey = 13;

        player1Name.getComponent<PositionComponent>().XPos = 750;
        player1Name.getComponent<PositionComponent>().YPos = 100;

        player1Gold.getComponent<PositionComponent>().XPos = 750;
        player1Gold.getComponent<PositionComponent>().YPos = 150;

        player1HeathPotion.getComponent<PositionComponent>().XPos = 750;
        player1HeathPotion.getComponent<PositionComponent>().YPos = 200;

        player1Armor.getComponent<PositionComponent>().XPos = 1050;
        player1Armor.getComponent<PositionComponent>().YPos = 150;

        player1ArmorMod.getComponent<PositionComponent>().XPos = 1050 + player1Armor.getComponent<TextComponent>().text.getLocalBounds().width;
        player1ArmorMod.getComponent<PositionComponent>().YPos = 150 ;

        player1Weapon.getComponent<PositionComponent>().XPos = 1050;
        player1Weapon.getComponent<PositionComponent>().YPos = 200;

        player1WeaponMod.getComponent<PositionComponent>().XPos = 1050 + player1Weapon.getComponent<TextComponent>().text.getLocalBounds().width;
        player1WeaponMod.getComponent<PositionComponent>().YPos = 200;

        createNew1.getComponent<AssosateFunc>().voidMenufunc = setPlayOption;
        anax::Entity PlayText1 = world.createEntity();
        drawebleText.setUpDrawebleText(PlayText1,"Play",cam,"Character",1,font,sf::Color().Black);
        PlayText1.getComponent<TextureComponent>().sortKey = 14;
        PlayText1.getComponent<PositionComponent>().XPos = 850+110;
        PlayText1.getComponent<PositionComponent>().YPos = 250+5;
    }else
    {
        createNew1.getComponent<AssosateFunc>().voidMenufunc = setNewCaracterOption;
        anax::Entity newCaraterText1 = world.createEntity();
        drawebleText.setUpDrawebleText(newCaraterText1,"New Character",cam,"Character",1,font,sf::Color().Black);
        newCaraterText1.getComponent<PositionComponent>().XPos = 850+50;
        newCaraterText1.getComponent<PositionComponent>().YPos = 250+5;
        newCaraterText1.getComponent<TextureComponent>().sortKey = 14;
    }

    anax::Entity createNew2 = world.createEntity();
    draweble.makeDraweble(getContext().textures->get(Textures::CharacterNew),850,250 +boxoffset,createNew2,"Character");
    createNew2.addComponent<MousedOver>();
    createNew2.addComponent<AssosateFunc>();
    createNew2.addComponent<MenuChoiceComponent>();
    createNew2.getComponent<TextureComponent>().sortKey = 12;

    if(secondFull)
    {
        anax::Entity player2Name = world.createEntity();
        anax::Entity player2Gold = world.createEntity();
        anax::Entity player2HeathPotion = world.createEntity();
        anax::Entity player2Armor = world.createEntity();
        anax::Entity player2ArmorMod = world.createEntity();
        anax::Entity player2Weapon = world.createEntity();
        anax::Entity player2WeaponMod = world.createEntity();

        drawebleText.setUpDrawebleText(player2Name,               "Name: " + file1Text.at(0),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player2Gold,               "Gold: " + file1Text.at(1),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player2HeathPotion,"Healt potion: " + file1Text.at(2),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player2Armor,             "Armor: " + file1Text.at(3),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player2ArmorMod,              " + " + file1Text.at(4),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player2Weapon,           "Weapon: " + file1Text.at(5),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player2WeaponMod,             " + " + file1Text.at(6),cam,"Character",1,font,sf::Color().Black);

        player2Name.getComponent<TextureComponent>().sortKey = 13;
        player2Gold.getComponent<TextureComponent>().sortKey = 13;
        player2HeathPotion.getComponent<TextureComponent>().sortKey = 13;
        player2Armor.getComponent<TextureComponent>().sortKey = 13;
        player2ArmorMod.getComponent<TextureComponent>().sortKey = 13;
        player2Weapon.getComponent<TextureComponent>().sortKey = 13;
        player2WeaponMod.getComponent<TextureComponent>().sortKey = 13;

        player2Name.getComponent<PositionComponent>().XPos = 750;
        player2Name.getComponent<PositionComponent>().YPos = 100 + boxoffset;

        player2Gold.getComponent<PositionComponent>().XPos = 750;
        player2Gold.getComponent<PositionComponent>().YPos = 150 + boxoffset;

        player2HeathPotion.getComponent<PositionComponent>().XPos = 750;
        player2HeathPotion.getComponent<PositionComponent>().YPos = 200 + boxoffset;

        player2Armor.getComponent<PositionComponent>().XPos = 1050;
        player2Armor.getComponent<PositionComponent>().YPos = 150 + boxoffset;

        player2ArmorMod.getComponent<PositionComponent>().XPos = 1050 + player2Armor.getComponent<TextComponent>().text.getLocalBounds().width;
        player2ArmorMod.getComponent<PositionComponent>().YPos = 150 + boxoffset;

        player2Weapon.getComponent<PositionComponent>().XPos = 1050;
        player2Weapon.getComponent<PositionComponent>().YPos = 200 + boxoffset;

        player2WeaponMod.getComponent<PositionComponent>().XPos = 1050 + player2Weapon.getComponent<TextComponent>().text.getLocalBounds().width;
        player2WeaponMod.getComponent<PositionComponent>().YPos = 200 + boxoffset;

        createNew2.getComponent<AssosateFunc>().voidMenufunc = setPlayOption;

        anax::Entity PlayText2 = world.createEntity();
        drawebleText.setUpDrawebleText(PlayText2,"Play",cam,"Character",1,font,sf::Color().Black);
        PlayText2.getComponent<PositionComponent>().XPos = 850+110;
        PlayText2.getComponent<PositionComponent>().YPos = 250+boxoffset+5;
        PlayText2.getComponent<TextureComponent>().sortKey = 14;
    }else
    {
        createNew2.getComponent<AssosateFunc>().voidMenufunc = setNewCaracterOption;
        anax::Entity newCaraterText2 = world.createEntity();
        drawebleText.setUpDrawebleText(newCaraterText2,"New Character",cam,"Character",1,font,sf::Color().Black);
        newCaraterText2.getComponent<PositionComponent>().XPos = 850+50;
        newCaraterText2.getComponent<PositionComponent>().YPos = 250+boxoffset +5;
        newCaraterText2.getComponent<TextureComponent>().sortKey = 14;
    }

    anax::Entity createNew3 = world.createEntity();
    draweble.makeDraweble(getContext().textures->get(Textures::CharacterNew),850,250 +boxoffset*2,createNew3,"Character");
    createNew3.addComponent<MousedOver>();
    createNew3.addComponent<AssosateFunc>();
    createNew3.addComponent<MenuChoiceComponent>();
    createNew3.getComponent<TextureComponent>().sortKey = 12;

    if(thirdFull)
    {
        anax::Entity player3Name = world.createEntity();
        anax::Entity player3Gold = world.createEntity();
        anax::Entity player3HeathPotion = world.createEntity();
        anax::Entity player3Armor = world.createEntity();
        anax::Entity player3ArmorMod = world.createEntity();
        anax::Entity player3Weapon = world.createEntity();
        anax::Entity player3WeaponMod = world.createEntity();

        drawebleText.setUpDrawebleText(player3Name,               "Name: " + file1Text.at(0),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player3Gold,               "Gold: " + file1Text.at(1),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player3HeathPotion,"Healt potion: " + file1Text.at(2),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player3Armor,             "Armor: " + file1Text.at(3),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player3ArmorMod,              " + " + file1Text.at(4),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player3Weapon,           "Weapon: " + file1Text.at(5),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player3WeaponMod,             " + " + file1Text.at(6),cam,"Character",1,font,sf::Color().Black);

        player3Name.getComponent<TextureComponent>().sortKey = 13;
        player3Gold.getComponent<TextureComponent>().sortKey = 13;
        player3HeathPotion.getComponent<TextureComponent>().sortKey = 13;
        player3Armor.getComponent<TextureComponent>().sortKey = 13;
        player3ArmorMod.getComponent<TextureComponent>().sortKey = 13;
        player3Weapon.getComponent<TextureComponent>().sortKey = 13;
        player3WeaponMod.getComponent<TextureComponent>().sortKey = 13;

        player3Name.getComponent<PositionComponent>().XPos = 750;
        player3Name.getComponent<PositionComponent>().YPos = 100 + boxoffset;

        player3Gold.getComponent<PositionComponent>().XPos = 750;
        player3Gold.getComponent<PositionComponent>().YPos = 150 + boxoffset;

        player3HeathPotion.getComponent<PositionComponent>().XPos = 750;
        player3HeathPotion.getComponent<PositionComponent>().YPos = 200 + boxoffset;

        player3Armor.getComponent<PositionComponent>().XPos = 1050;
        player3Armor.getComponent<PositionComponent>().YPos = 150 + boxoffset;

        player3ArmorMod.getComponent<PositionComponent>().XPos = 1050 + player3Armor.getComponent<TextComponent>().text.getLocalBounds().width;
        player3ArmorMod.getComponent<PositionComponent>().YPos = 150 + boxoffset;

        player3Weapon.getComponent<PositionComponent>().XPos = 1050;
        player3Weapon.getComponent<PositionComponent>().YPos = 200 + boxoffset;

        player3WeaponMod.getComponent<PositionComponent>().XPos = 1050 + player3Weapon.getComponent<TextComponent>().text.getLocalBounds().width;
        player3WeaponMod.getComponent<PositionComponent>().YPos = 200 + boxoffset;

        createNew3.getComponent<AssosateFunc>().voidMenufunc = setPlayOption;

        anax::Entity PlayText3 = world.createEntity();
        drawebleText.setUpDrawebleText(PlayText3,"Play",cam,"Character",1,font,sf::Color().Black);
        PlayText3.getComponent<PositionComponent>().XPos = 850+110;
        PlayText3.getComponent<PositionComponent>().YPos = 250+boxoffset*2+5;
        PlayText3.getComponent<TextureComponent>().sortKey = 14;
    }else
    {
        createNew3.getComponent<AssosateFunc>().voidMenufunc = setNewCaracterOption;

        anax::Entity newCaraterText3 = world.createEntity();
        drawebleText.setUpDrawebleText(newCaraterText3,"New Character",cam,"Character",1,font,sf::Color().Black);
        newCaraterText3.getComponent<PositionComponent>().XPos = 850+50;
        newCaraterText3.getComponent<PositionComponent>().YPos = 250+boxoffset*2+5;
        newCaraterText3.getComponent<TextureComponent>().sortKey = 14;
    }





}
void StateCharacter::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    anax::World& world = *getContext().world;
    DrawEntetys drawEntetys;
    drawEntetys.draw(window,world,"Character");

}

bool StateCharacter::update(sf::Time dt)
{
    return true;
}

bool StateCharacter::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Game);
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {

    }

    return true;
}

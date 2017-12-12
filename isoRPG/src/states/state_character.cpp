#include <include/collections/drawable.h>
#include <include/systems/drawEntety.h>
#include <fstream>
#include <include/collections/drawebleText.h>
#include <include/components/Comp_AssosiateFunc.h>
#include <include/collections/mouseClikedFunctions.h>
#include <include/components/Comp_Menuchoice.h>
#include <include/systems/mouseClickedMenus.h>
#include <include/components/Comp_save.h>
#include "include/states/state_character.h"
#include "include/gameEngine/resource_holder.h"

StateCharacter::StateCharacter(StateStack &stack, Context context)
        : StateBase(stack, context)
{

    setUpSaves();


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
        //requestStackPop();
        //requestStackPush(States::Game);
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        mouseClickedMenus mouseClickedMenus(getContext());
        mouseClickedMenus.Clicked();

        anax::World& world = *getContext().world;
        std::string choice = "";
        std::string source = "";
        auto entitys = world.getEntities();
        for(auto i : entitys)
        {
            if(i.hasComponent<MenuChoiceComponent>())
            {
                if(i.getComponent<MenuChoiceComponent>().choice == "Game")
                {
                    choice = "Game";
                    getContext().sounds->play(SoundEffects::Click);
                    source = i.getComponent<MenuChoiceComponent>().source;

                }
                if(i.getComponent<MenuChoiceComponent>().choice == "New")
                {
                    choice = "New";
                    getContext().sounds->play(SoundEffects::Click);
                    source = i.getComponent<MenuChoiceComponent>().source;
                }
                if(i.getComponent<MenuChoiceComponent>().choice == "Renew")
                {
                    auto enteties = world.getEntities();
                    choice = "Renew";
                    if(i.getComponent<MenuChoiceComponent>().source == "delete1")
                    {
                        for(auto i : enteties)
                        {
                            if(i.getComponent<TextureComponent>().sortKey == 15)i.kill();
                        }
                    }
                    if(i.getComponent<MenuChoiceComponent>().source == "delete2")
                    {
                        for(auto i : enteties)
                        {
                            if(i.getComponent<TextureComponent>().sortKey == 16) i.kill();
                        }
                    }
                    if(i.getComponent<MenuChoiceComponent>().source == "delete3")
                    {
                        for(auto i : enteties)
                        {
                            if(i.getComponent<TextureComponent>().sortKey == 17)i.kill();
                        }
                    }
                    getContext().sounds->play(SoundEffects::Click);
                    world.refresh();
                    choice = "Renew";
                }

            }
        }

        if(choice != "")
        {
            anax::World& world = *getContext().world;
            auto enteties = world.getEntities();
            for(auto i : enteties)
            {
                i.kill();
                world.refresh();
            }

            anax::Entity save = world.createEntity();
            save.addComponent<SaveComponent>();
            if(source == "Save1")
            {
                save.getComponent<SaveComponent>().number = 1;
                save.getComponent<SaveComponent>().file = "assets/saves/save1.txt";
            }
            if(source == "Save2")
            {
                save.getComponent<SaveComponent>().number = 2;
                save.getComponent<SaveComponent>().file = "assets/saves/save2.txt";
            }
            if(source == "Save3")
            {
                save.getComponent<SaveComponent>().number = 3;
                save.getComponent<SaveComponent>().file = "assets/saves/save3.txt";
            }

            if(choice == "Game") requestStateChange(States::Game);
            if(choice == "New")  requestStateChange(States::CharacterCreation);

            if(choice == "Renew")
            {
                save.kill();
                world.refresh();
                setUpSaves();
            }


        }

    }

    return true;
}

void StateCharacter::setUpSaves()
{
    sf::Font& font = getContext().fonts->get(Fonts::RPG);

    anax::World& world = *getContext().world;
    sf::RenderWindow& window = *getContext().window;

    anax::Entity background = world.createEntity();

    anax::Entity saveSlot1 = world.createEntity();
    anax::Entity saveSlot2 = world.createEntity();
    anax::Entity saveSlot3 = world.createEntity();

    Draweble draweble;

    draweble.makeDraweble(getContext().textures->get(Textures::SettingsBackdorp),0,0,background,"Character");

    float boxoffset = 300;
    draweble.makeDraweble(getContext().textures->get(Textures::CharacterBox),500,80,saveSlot1,"Character");
    draweble.makeDraweble(getContext().textures->get(Textures::CharacterBox),500,80 + boxoffset,saveSlot2,"Character");
    draweble.makeDraweble(getContext().textures->get(Textures::CharacterBox),500,80 + boxoffset*2,saveSlot3,"Character");

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
    if(nr > 6) firstFull = true;
    nr = 0;
    while (std::getline(file2, tempstring))
    {
        file2Text[nr] = tempstring;
        nr++;
    }
    if(nr > 6) secondFull = true;
    nr = 0;
    while (std::getline(file3, tempstring))
    {
        file3Text[nr] = tempstring;
        nr++;
    }
    if(nr > 6) thirdFull = true;

    DrawebleText drawebleText;
    sf::View cam= window.getView();

    anax::Entity createNew1 = world.createEntity();
    draweble.makeDraweble(getContext().textures->get(Textures::CharacterNew),850,250,createNew1,"Character");
    createNew1.getComponent<TextureComponent>().sortKey = 12;
    createNew1.addComponent<MousedOver>();
    createNew1.addComponent<AssosateFunc>();
    createNew1.addComponent<MenuChoiceComponent>();
    createNew1.getComponent<MenuChoiceComponent>().source = "Save1";

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

        player1Name.getComponent<TextureComponent>().sortKey = 15;
        player1Gold.getComponent<TextureComponent>().sortKey = 15;
        player1HeathPotion.getComponent<TextureComponent>().sortKey = 15;
        player1Armor.getComponent<TextureComponent>().sortKey = 15;
        player1ArmorMod.getComponent<TextureComponent>().sortKey = 15;
        player1Weapon.getComponent<TextureComponent>().sortKey = 15;
        player1WeaponMod.getComponent<TextureComponent>().sortKey = 15;

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
        PlayText1.getComponent<TextureComponent>().sortKey = 15;
        PlayText1.getComponent<PositionComponent>().XPos = 850+110;
        PlayText1.getComponent<PositionComponent>().YPos = 250+5;

        anax::Entity delete1 = world.createEntity();
        draweble.makeDraweble(getContext().textures->get(Textures::UIRedX),1000 + saveSlot1.getComponent<SizeComponent>().Height-50,95,delete1,"Character");
        delete1.getComponent<TextureComponent>().sortKey = 15;
        delete1.getComponent<TextureComponent>().sprite[0].setScale(0.2f,0.2f);

        delete1.addComponent<MenuChoiceComponent>();
        delete1.getComponent<MenuChoiceComponent>().source = "delete1";
        delete1.addComponent<MousedOver>();
        delete1.addComponent<AssosateFunc>();
        delete1.getComponent<AssosateFunc>().voidMenufunc = setRenewOption;

    }else
    {
        createNew1.getComponent<AssosateFunc>().voidMenufunc = setNewCaracterOption;
        anax::Entity newCaraterText1 = world.createEntity();
        drawebleText.setUpDrawebleText(newCaraterText1,"New Character",cam,"Character",1,font,sf::Color().Black);
        newCaraterText1.getComponent<PositionComponent>().XPos = 850+50;
        newCaraterText1.getComponent<PositionComponent>().YPos = 250+5;
        newCaraterText1.getComponent<TextureComponent>().sortKey = 15;
    }

    anax::Entity createNew2 = world.createEntity();
    draweble.makeDraweble(getContext().textures->get(Textures::CharacterNew),850,250 +boxoffset,createNew2,"Character");
    createNew2.addComponent<MousedOver>();
    createNew2.addComponent<AssosateFunc>();
    createNew2.addComponent<MenuChoiceComponent>();
    createNew2.getComponent<MenuChoiceComponent>().source = "Save2";
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

        drawebleText.setUpDrawebleText(player2Name,               "Name: " + file2Text.at(0),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player2Gold,               "Gold: " + file2Text.at(1),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player2HeathPotion,"Healt potion: " + file2Text.at(2),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player2Armor,             "Armor: " + file2Text.at(3),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player2ArmorMod,              " + " + file2Text.at(4),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player2Weapon,           "Weapon: " + file2Text.at(5),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player2WeaponMod,             " + " + file2Text.at(6),cam,"Character",1,font,sf::Color().Black);

        player2Name.getComponent<TextureComponent>().sortKey = 16;
        player2Gold.getComponent<TextureComponent>().sortKey = 16;
        player2HeathPotion.getComponent<TextureComponent>().sortKey = 16;
        player2Armor.getComponent<TextureComponent>().sortKey = 16;
        player2ArmorMod.getComponent<TextureComponent>().sortKey = 16;
        player2Weapon.getComponent<TextureComponent>().sortKey = 16;
        player2WeaponMod.getComponent<TextureComponent>().sortKey = 16;

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
        PlayText2.getComponent<TextureComponent>().sortKey = 16;

        anax::Entity delete2 = world.createEntity();
        draweble.makeDraweble(getContext().textures->get(Textures::UIRedX),1000 + saveSlot1.getComponent<SizeComponent>().Height-50,95+boxoffset,delete2,"Character");
        delete2.getComponent<TextureComponent>().sortKey = 16;
        delete2.getComponent<TextureComponent>().sprite[0].setScale(0.2f,0.2f);


        delete2.addComponent<MenuChoiceComponent>();
        delete2.getComponent<MenuChoiceComponent>().source = "delete2";
        delete2.addComponent<MousedOver>();
        delete2.addComponent<AssosateFunc>();
        delete2.getComponent<AssosateFunc>().voidMenufunc = setRenewOption;
    }else
    {
        createNew2.getComponent<AssosateFunc>().voidMenufunc = setNewCaracterOption;
        anax::Entity newCaraterText2 = world.createEntity();
        drawebleText.setUpDrawebleText(newCaraterText2,"New Character",cam,"Character",1,font,sf::Color().Black);
        newCaraterText2.getComponent<PositionComponent>().XPos = 850+50;
        newCaraterText2.getComponent<PositionComponent>().YPos = 250+boxoffset +5;
        newCaraterText2.getComponent<TextureComponent>().sortKey = 16;
    }

    anax::Entity createNew3 = world.createEntity();
    draweble.makeDraweble(getContext().textures->get(Textures::CharacterNew),850,250 +boxoffset*2,createNew3,"Character");
    createNew3.addComponent<MousedOver>();
    createNew3.addComponent<AssosateFunc>();
    createNew3.addComponent<MenuChoiceComponent>();
    createNew3.getComponent<MenuChoiceComponent>().source = "Save3";
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

        drawebleText.setUpDrawebleText(player3Name,               "Name: " + file3Text.at(0),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player3Gold,               "Gold: " + file3Text.at(1),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player3HeathPotion,"Healt potion: " + file3Text.at(2),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player3Armor,             "Armor: " + file3Text.at(3),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player3ArmorMod,              " + " + file3Text.at(4),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player3Weapon,           "Weapon: " + file3Text.at(5),cam,"Character",1,font,sf::Color().Black);
        drawebleText.setUpDrawebleText(player3WeaponMod,             " + " + file3Text.at(6),cam,"Character",1,font,sf::Color().Black);

        player3Name.getComponent<TextureComponent>().sortKey = 17;
        player3Gold.getComponent<TextureComponent>().sortKey = 17;
        player3HeathPotion.getComponent<TextureComponent>().sortKey = 17;
        player3Armor.getComponent<TextureComponent>().sortKey = 17;
        player3ArmorMod.getComponent<TextureComponent>().sortKey = 17;
        player3Weapon.getComponent<TextureComponent>().sortKey = 17;
        player3WeaponMod.getComponent<TextureComponent>().sortKey = 17;

        player3Name.getComponent<PositionComponent>().XPos = 750;
        player3Name.getComponent<PositionComponent>().YPos = 100 + boxoffset*2;

        player3Gold.getComponent<PositionComponent>().XPos = 750;
        player3Gold.getComponent<PositionComponent>().YPos = 150 + boxoffset*2;

        player3HeathPotion.getComponent<PositionComponent>().XPos = 750;
        player3HeathPotion.getComponent<PositionComponent>().YPos = 200 + boxoffset*2;

        player3Armor.getComponent<PositionComponent>().XPos = 1050;
        player3Armor.getComponent<PositionComponent>().YPos = 150 + boxoffset*2;

        player3ArmorMod.getComponent<PositionComponent>().XPos = 1050 + player3Armor.getComponent<TextComponent>().text.getLocalBounds().width;
        player3ArmorMod.getComponent<PositionComponent>().YPos = 150 + boxoffset*2;

        player3Weapon.getComponent<PositionComponent>().XPos = 1050;
        player3Weapon.getComponent<PositionComponent>().YPos = 200 + boxoffset*2;

        player3WeaponMod.getComponent<PositionComponent>().XPos = 1050 + player3Weapon.getComponent<TextComponent>().text.getLocalBounds().width;
        player3WeaponMod.getComponent<PositionComponent>().YPos = 200 + boxoffset*2;

        createNew3.getComponent<AssosateFunc>().voidMenufunc = setPlayOption;

        anax::Entity PlayText3 = world.createEntity();
        drawebleText.setUpDrawebleText(PlayText3,"Play",cam,"Character",1,font,sf::Color().Black);
        PlayText3.getComponent<PositionComponent>().XPos = 850+110;
        PlayText3.getComponent<PositionComponent>().YPos = 250+boxoffset*2+5;
        PlayText3.getComponent<TextureComponent>().sortKey = 17;

        anax::Entity delete3 = world.createEntity();
        draweble.makeDraweble(getContext().textures->get(Textures::UIRedX),1000 + saveSlot1.getComponent<SizeComponent>().Height-50,95+boxoffset*2,delete3,"Character");
        delete3.getComponent<TextureComponent>().sortKey = 17;
        delete3.getComponent<TextureComponent>().sprite[0].setScale(0.2f,0.2f);

        delete3.addComponent<MenuChoiceComponent>();
        delete3.getComponent<MenuChoiceComponent>().source = "delete3";
        delete3.addComponent<MousedOver>();
        delete3.addComponent<AssosateFunc>();
        delete3.getComponent<AssosateFunc>().voidMenufunc = setRenewOption;
    }else
    {
        createNew3.getComponent<AssosateFunc>().voidMenufunc = setNewCaracterOption;

        anax::Entity newCaraterText3 = world.createEntity();
        drawebleText.setUpDrawebleText(newCaraterText3,"New Character",cam,"Character",1,font,sf::Color().Black);
        newCaraterText3.getComponent<PositionComponent>().XPos = 850+50;
        newCaraterText3.getComponent<PositionComponent>().YPos = 250+boxoffset*2+5;
        newCaraterText3.getComponent<TextureComponent>().sortKey = 17;
    }


}

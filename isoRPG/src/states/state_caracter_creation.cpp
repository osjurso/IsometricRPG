
#include <include/systems/mouseClickedMenus.h>
#include <include/components/Comp_save.h>
#include <include/collections/drawable.h>
#include <include/systems/drawEntety.h>
#include <include/collections/drawebleText.h>
#include <include/collections/mouseClikedFunctions.h>
#include <include/components/Comp_Menuchoice.h>
#include <fstream>
#include "include/states/state_caracter_creation.h"

StateCaracterCreation::StateCaracterCreation(StateStack &stack, Context context) : StateBase(stack, context)
{
    anax::World& world = *getContext().world;
    sf::RenderWindow& window = *getContext().window;
    sf::Font& font = context.fonts->get(Fonts::RPG);
    sf::View cam = window.getView();


    auto entitys = world.getEntities();
    for(auto i : entitys)
    {
        if(i.hasComponent<SaveComponent>())
        {
            if(i.getComponent<SaveComponent>().number != -1)
            {
                saveNr = i.getComponent<SaveComponent>().number;
                saveFile = i.getComponent<SaveComponent>().file;
                std::cout << saveFile << std::endl;
                i.kill();
                world.refresh();
            }
        }
    }

    anax::Entity background = world.createEntity();
    Draweble draweble;
    DrawebleText drawebleText;

    draweble.makeDraweble(context.textures->get(Textures::SettingsBackdorp),0,0,background,"CharacterCreation");
    background.getComponent<TextureComponent>().sortKey = 10;

    anax::Entity nameText = world.createEntity();
    drawebleText.setUpDrawebleText(nameText,"Name: ", cam,"CharacterCreation",1,font,sf::Color().Black);
    nameText.getComponent<PositionComponent>().XPos = 300;
    nameText.getComponent<PositionComponent>().YPos = 100;

    CaracterName = world.createEntity();
    drawebleText.setUpDrawebleText(CaracterName,"",cam,"CharacterCreation",1,font,sf::Color().Black);
    CaracterName.getComponent<PositionComponent>().XPos = 300 + nameText.getComponent<SizeComponent>().Whith;
    CaracterName.getComponent<PositionComponent>().YPos = 100;

    anax::Entity playButton = world.createEntity();
    draweble.makeDraweble(getContext().textures->get(Textures::CharacterNew),cam.getCenter().x,cam.getSize().y -200,playButton,"CharacterCreation");
    playButton.getComponent<PositionComponent>().XPos = playButton.getComponent<PositionComponent>().XPos - playButton.getComponent<TextureComponent>().sprite->getLocalBounds().width/2;
    playButton.getComponent<TextureComponent>().sortKey = 12;
    playButton.addComponent<MousedOver>();
    playButton.addComponent<AssosateFunc>();
    playButton.getComponent<AssosateFunc>().voidMenufunc = setPlayOption;
    playButton.addComponent<MenuChoiceComponent>();

    anax::Entity PlayText = world.createEntity();
    drawebleText.setUpDrawebleText(PlayText,"Play",cam,"CharacterCreation",1,font,sf::Color().Black);
    PlayText.getComponent<PositionComponent>().XPos = cam.getCenter().x- PlayText.getComponent<TextComponent>().text.getLocalBounds().width/2;
    PlayText.getComponent<PositionComponent>().YPos = cam.getSize().y -200 +8;
    PlayText.getComponent<TextureComponent>().sortKey = 13;
}

void StateCaracterCreation::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    anax::World& world = *getContext().world;
    DrawEntetys drawEntetys;
    drawEntetys.draw(window,world,"CharacterCreation");

}

bool StateCaracterCreation::update(sf::Time dt)
{

    CaracterName.getComponent<TextComponent>().text.setString(caracterNameText);
    return true;

}

bool StateCaracterCreation::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if(typing)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) caracterNameText += "A";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)) caracterNameText += "B";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)) caracterNameText += "C";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) caracterNameText += "D";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) caracterNameText += "E";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)) caracterNameText += "F";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)) caracterNameText += "G";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)) caracterNameText += "H";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)) caracterNameText += "I";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)) caracterNameText += "J";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)) caracterNameText += "K";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) caracterNameText += "L";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)) caracterNameText += "M";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)) caracterNameText += "N";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)) caracterNameText += "O";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) caracterNameText += "P";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) caracterNameText += "Q";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) caracterNameText += "R";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) caracterNameText += "S";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)) caracterNameText += "T";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)) caracterNameText += "U";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)) caracterNameText += "V";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) caracterNameText += "W";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) caracterNameText += "X";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) caracterNameText += "Y";
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) caracterNameText += "Z";

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && caracterNameText.length() > 0) caracterNameText.erase(caracterNameText.length()-1, caracterNameText.length());


        }

    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        mouseClickedMenus mouseClickedMenus(getContext());
        mouseClickedMenus.Clicked();

        anax::World& world = *getContext().world;
        std::string choice = "";
        auto entitys = world.getEntities();
        for(auto i : entitys)
        {
            if(i.hasComponent<MenuChoiceComponent>())
            {
                if(i.getComponent<MenuChoiceComponent>().choice == "Game")
                {
                    choice = "Game";
                    getContext().sounds->play(SoundEffects::Click);

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
            save.getComponent<SaveComponent>().file = saveFile;
            save.getComponent<SaveComponent>().number = saveNr;

            std::ofstream ofs;
            ofs.open (saveFile, std::ofstream::out | std::ofstream::app);

            ofs << caracterNameText << std::endl;
            ofs << "0" << std::endl;
            ofs << "3" << std::endl;
            ofs << "10" << std::endl;
            ofs << "0" << std::endl;
            ofs << "10" << std::endl;
            ofs << "0" << std::endl;

            ofs.close();
            //read form file
            // 1. Name
            // 2. Gold
            // 3: Healt potion
            // 4. Armor
            // 5. Armor mod
            // 6. Weapon
            // 7. Weapon mod

            if(choice == "Game") requestStateChange(States::Game);


        }

    }

    return true;
}

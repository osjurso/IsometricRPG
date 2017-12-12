#include <SFML/Graphics/RenderWindow.hpp>
#include <include/systems/drawEntety.h>
#include <include/systems/mouse_clicked.h>
#include <include/systems/mouseClickedMenus.h>
#include <include/components/Comp_Menuchoice.h>
#include <include/collections/setUpRectShape.h>
#include "include/states/state_menu.h"
#include "include/util/utility.h"
#include "collections/drawable.h"
#include "collections/mouseClikedFunctions.h"

StateMenu::StateMenu(StateStack& stack, Context context)
        : StateBase(stack, context)
        , mOptions()
        , mOptionIndex(0)
{
    sf::Font& font = context.fonts->get(Fonts::RPG);
    sf::RenderWindow& window = *getContext().window;

    mLogoSprite.setTexture(context.textures->get(Textures::TitleText));
    mBackdrop.setTexture(context.textures->get(Textures::MenuBackdrop));
    mFire.setTexture(context.textures->get(Textures::MenuFire));

    fireSpriteSize = 265;
    spriteRect.top = 0;
    spriteRect.left = 0;
    spriteRect.height = fireSpriteSize;
    spriteRect.width = fireSpriteSize;

    clock.restart();
    mFire.setTextureRect(spriteRect);


    centerOrigin(mLogoSprite);
    mLogoSprite.setPosition(context.window->getSize().x / 2, context.window->getSize().y / 4);
    mBackdrop.setPosition(0,0);

    mFire2 = mFire;

    mFire.setPosition(530,90); //TODO: do dynamacly
    mFire2.setPosition(1130,90);


    anax::Entity PlayOption = getContext().world->createEntity();
    anax::Entity SettingsOption = getContext().world->createEntity();
    anax::Entity AboutOption = getContext().world->createEntity();
    anax::Entity ExitOption = getContext().world->createEntity();


    DrawebleText drawebleText;
    sf::View cam = getContext().window->getView();
    drawebleText.setUpDrawebleText(PlayOption    ,"Play"    ,cam,"Menu",1.0f,font,sf::Color().White);
    drawebleText.setUpDrawebleText(SettingsOption,"Settings",cam,"Menu",1.0f,font,sf::Color().White);
    drawebleText.setUpDrawebleText(AboutOption   ,"About"   ,cam,"Menu",1.0f,font,sf::Color().White);
    drawebleText.setUpDrawebleText(ExitOption    ,"Exit"    ,cam,"Menu",1.0f,font,sf::Color().White);

    PlayOption.addComponent<MousedOver>();
    PlayOption.addComponent<AssosateFunc>();
    PlayOption.getComponent<AssosateFunc>().voidMenufunc =  setPlayOption;
    PlayOption.addComponent<MenuChoiceComponent>();


    SettingsOption.addComponent<MousedOver>();
    SettingsOption.addComponent<AssosateFunc>();
    SettingsOption.getComponent<AssosateFunc>().voidMenufunc = setSettingsOption;
    SettingsOption.addComponent<MenuChoiceComponent>();


    AboutOption.addComponent<MousedOver>();
    AboutOption.addComponent<AssosateFunc>();
    AboutOption.getComponent<AssosateFunc>().voidMenufunc = setAboutOption;
    AboutOption.addComponent<MenuChoiceComponent>();


    ExitOption.addComponent<MousedOver>();
    ExitOption.addComponent<AssosateFunc>();
    ExitOption.getComponent<AssosateFunc>().voidMenufunc = setExitOption;
    ExitOption.addComponent<MenuChoiceComponent>();


    int nr =0;
    PlayOption.getComponent<PositionComponent>().XPos = cam.getCenter().x - PlayOption.getComponent<TextComponent>().text.getLocalBounds().width/2;
    PlayOption.getComponent<PositionComponent>().YPos = cam.getCenter().y -250 - PlayOption.getComponent<TextComponent>().text.getLocalBounds().height/2;
    PlayOption.getComponent<PositionComponent>().SpriteLeft = PlayOption.getComponent<PositionComponent>().XPos;
    PlayOption.getComponent<PositionComponent>().SpriteTop = PlayOption.getComponent<PositionComponent>().YPos;
    nr++;
    SettingsOption.getComponent<PositionComponent>().XPos = cam.getCenter().x - SettingsOption.getComponent<TextComponent>().text.getLocalBounds().width/2;
    SettingsOption.getComponent<PositionComponent>().YPos = cam.getCenter().y -250 + nr*35 - PlayOption.getComponent<TextComponent>().text.getLocalBounds().height/2;
    SettingsOption.getComponent<PositionComponent>().SpriteLeft = SettingsOption.getComponent<PositionComponent>().XPos;
    SettingsOption.getComponent<PositionComponent>().SpriteTop = SettingsOption.getComponent<PositionComponent>().YPos;
    nr++;
    AboutOption.getComponent<PositionComponent>().XPos = cam.getCenter().x - AboutOption.getComponent<TextComponent>().text.getLocalBounds().width/2;
    AboutOption.getComponent<PositionComponent>().YPos = cam.getCenter().y -250 + nr*35 - PlayOption.getComponent<TextComponent>().text.getLocalBounds().height/2 -1;
    AboutOption.getComponent<PositionComponent>().SpriteLeft = AboutOption.getComponent<PositionComponent>().XPos;
    AboutOption.getComponent<PositionComponent>().SpriteTop = AboutOption.getComponent<PositionComponent>().YPos;
    nr++;
    ExitOption.getComponent<PositionComponent>().XPos = cam.getCenter().x - ExitOption.getComponent<TextComponent>().text.getLocalBounds().width/2;
    ExitOption.getComponent<PositionComponent>().YPos = cam.getCenter().y -250 + nr*35 - PlayOption.getComponent<TextComponent>().text.getLocalBounds().height/2;
    ExitOption.getComponent<PositionComponent>().SpriteLeft = ExitOption.getComponent<PositionComponent>().XPos;
    ExitOption.getComponent<PositionComponent>().SpriteTop = ExitOption.getComponent<PositionComponent>().YPos;




    // Creating menu choices
    sf::Text playOption;
    playOption.setFont(font);
    playOption.setString("Play");
    centerOrigin(playOption);
    playOption.setPosition(context.window->getView().getSize() / 2.f);
    playOption.move(0,-250);
    mOptions.push_back(playOption);

    sf::Text settingsOption;
    settingsOption.setFont(font);
    settingsOption.setString("Settings");
    centerOrigin(settingsOption);
    settingsOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 35.f));
    mOptions.push_back(settingsOption);

    sf::Text aboutOption;
    aboutOption.setFont(font);
    aboutOption.setString("About");
    centerOrigin(aboutOption);
    aboutOption.setPosition(settingsOption.getPosition() + sf::Vector2f(0.f, 35.f));
    mOptions.push_back(aboutOption);

    sf::Text exitOption;
    exitOption.setFont(font);
    exitOption.setString("Exit");
    centerOrigin(exitOption);
    exitOption.setPosition(aboutOption.getPosition() + sf::Vector2f(0.f, 35.f));
    mOptions.push_back(exitOption);


    anax::World& world = *getContext().world;;

    Draweble draweble;
    sf::Texture& texture = context.textures->get(Textures::TitleLogo);
    sf::Texture& menuBackdrop = context.textures->get(Textures::MenuBackdrop);

    anax::Entity menuBackdropEntity = world.createEntity();
    draweble.makeDraweble(menuBackdrop,0,0,menuBackdropEntity,"Menu");
    updateOptionText();

    context.music->play(Music::Menu);
}

void StateMenu::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());


    anax::World& world = *getContext().world;
    DrawEntetys drawEntetys;
    drawEntetys.draw(window,world,"Menu");


    for (const sf::Text& text : mOptions)
        window.draw(text);
}

bool StateMenu::update(sf::Time)
{
    if(clock.getElapsedTime().asSeconds() > 0.10f)
    {
        if(spriteRect.left == 3*fireSpriteSize)
        {
            StateMenu::spriteRect.left = 0;
            StateMenu::spriteRect.top += fireSpriteSize;
            if(spriteRect.top == 2*fireSpriteSize)
                spriteRect.top = 0;
        }else
            StateMenu::spriteRect.left += fireSpriteSize;

        mFire.setTextureRect(spriteRect);
        mFire2.setTextureRect(spriteRect);
        clock.restart();
    }
    //sf::RenderWindow window = *getContext().window;


    return true;
}

bool StateMenu::handleEvent(const sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Return)
        {
            if (mOptionIndex == Play)
            {
                anax::World& world = *getContext().world;
                auto enteties = world.getEntities();
                for(auto i : enteties)
                {
                    i.kill();
                    world.refresh();
                }
                requestStateChange(States::Character);

            }
            else if (mOptionIndex == Settings)
            {
                anax::World& world = *getContext().world;
                auto enteties = world.getEntities();
                for(auto i : enteties)
                {
                    i.kill();
                    world.refresh();
                }
                requestStateChange(States::Settings);
            }
            else if (mOptionIndex == About)
            {

            }
            else if (mOptionIndex == Exit)
            {
                requestStackPop();
            }
        }

        else if (event.key.code == sf::Keyboard::Up|| event.key.code == sf::Keyboard::W)
        {
            if (mOptionIndex > 0)
                mOptionIndex--;
            else
                mOptionIndex = mOptions.size() - 1;

            updateOptionText();
            getContext().sounds->play(SoundEffects::Click);
        }

        else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
        {
            if (mOptionIndex < mOptions.size() - 1)
                mOptionIndex++;
            else
                mOptionIndex = 0;

            updateOptionText();
            getContext().sounds->play(SoundEffects::Click);
        }
    }

    if(event.type == sf::Event::MouseButtonPressed)
    {
        mouseClickedMenus mouseClickedMenus1(getContext());
        mouseClickedMenus1.Clicked();

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
                if(i.getComponent<MenuChoiceComponent>().choice == "Settings")
                {
                    choice = "Settings";
                    getContext().sounds->play(SoundEffects::Click);
                }
                if(i.getComponent<MenuChoiceComponent>().choice == "About")
                {
                    choice = "About";
                    getContext().sounds->play(SoundEffects::Click);
                }
                if(i.getComponent<MenuChoiceComponent>().choice == "Exit")
                {
                    requestStackPop();
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
            if(choice == "Game") requestStateChange(States::Character);
            if(choice == "Settings") requestStateChange(States::Settings);
            if(choice == "About") requestStateChange(States::Character);
        }
    }

    return true;
}

void StateMenu::updateOptionText()
{
    if (mOptions.empty())
        return;

    for (sf::Text& text : mOptions)
        text.setFillColor(sf::Color::White);

    mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}

#include <SFML/Graphics/RenderWindow.hpp>
#include <include/systems/drawEntety.h>
#include <include/systems/mouse_clicked.h>
#include "include/states/state_menu.h"
#include "include/util/utility.h"
#include "include/collections/drawable.h"

StateMenu::StateMenu(StateStack& stack, Context context)
        : StateBase(stack, context)
        , mOptions()
        , mOptionIndex(0)
{
    sf::Font& font = context.fonts->get(Fonts::RPG);

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
    drawebleText.setUpDrawebleText(PlayOption    ,"Play"    ,cam,"Menu",1,font,sf::Color().White);
    drawebleText.setUpDrawebleText(SettingsOption,"Settings",cam,"Menu",1,font,sf::Color().White);
    drawebleText.setUpDrawebleText(AboutOption   ,"About"   ,cam,"Menu",1,font,sf::Color().White);
    drawebleText.setUpDrawebleText(ExitOption    ,"Exit"    ,cam,"Menu",1,font,sf::Color().White);

    int nr =0;
    PlayOption.getComponent<PositionComponent>().XPos = cam.getCenter().x - PlayOption.getComponent<TextComponent>().text.getLocalBounds().width/2;
    PlayOption.getComponent<PositionComponent>().YPos = cam.getCenter().y -250 - PlayOption.getComponent<TextComponent>().text.getLocalBounds().height/2;
    nr++;
    SettingsOption.getComponent<PositionComponent>().XPos = cam.getCenter().x - SettingsOption.getComponent<TextComponent>().text.getLocalBounds().width/2;
    SettingsOption.getComponent<PositionComponent>().YPos = cam.getCenter().y -250 + nr*35 - PlayOption.getComponent<TextComponent>().text.getLocalBounds().height/2;
    nr++;
    AboutOption.getComponent<PositionComponent>().XPos = cam.getCenter().x - AboutOption.getComponent<TextComponent>().text.getLocalBounds().width/2;
    AboutOption.getComponent<PositionComponent>().YPos = cam.getCenter().y -250 + nr*35 - PlayOption.getComponent<TextComponent>().text.getLocalBounds().height/2 -1;
    nr++;
    ExitOption.getComponent<PositionComponent>().XPos = cam.getCenter().x - ExitOption.getComponent<TextComponent>().text.getLocalBounds().width/2;
    ExitOption.getComponent<PositionComponent>().YPos = cam.getCenter().y -250 + nr*35 - PlayOption.getComponent<TextComponent>().text.getLocalBounds().height/2;


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


    if(event.type == sf::Event::MouseButtonPressed)
    {
        MouseClicked mouseClicked(getContext());
        anax::Entity entity = getContext().world->createEntity();
        mouseClicked.Clicked(entity,getContext().window->getView(),1,"Menu");

    }
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

#include <SFML/Graphics/RenderWindow.hpp>
#include <include/systems/drawEntety.h>
#include <include/systems/mouse_clicked.h>
#include <include/components/Player.h>
#include <include/components/Comp_aniamteble.h>
#include "include/states/state_menu.h"
#include "include/util/utility.h"
#include "include/collections/drawable.h"

StateMenu::StateMenu(StateStack& stack, Context context)
        : StateBase(stack, context)
        , mOptions()
        , mOptionIndex(0)
{
    sf::Font& font = context.fonts->get(Fonts::Main);

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

    //PositionComponent& positionComponent = e.getComponent<PositionComponent>();

    anax::World& world = *getContext().world;

    Draweble draweble;
    sf::Texture& texture = context.textures->get(Textures::TitleLogo);
    sf::Texture& menuBackdrop = context.textures->get(Textures::MenuBackdrop);
    sf::Texture& hero = context.textures->get(Textures::tempHero);
    Player player(hero, sf::Vector2u(32,8), 0.2f, 100.f);

    anax::Entity menuBackdropEntity = world.createEntity();
    //anax::Entity logo1 = world.createEntity();
    //anax::Entity logo2 = world.createEntity();
    anax::Entity hero1 = world.createEntity();
    hero1.addComponent<Animated>();
    player.walk(clock.getElapsedTime().asSeconds());

    //logo1.addComponent<MousedOver>();
    //logo2.addComponent<MousedOver>();

    draweble.makeDraweble(menuBackdrop,0,0,menuBackdropEntity);
    //draweble.makeDraweble(texture,300,500, logo1);
    //draweble.makeDraweble(texture,800,500, logo2);
    draweble.makeDraweble(hero, 100, 200, hero1);
    updateOptionText();



    player.walk(clock.getElapsedTime().asSeconds());

    context.music->play(Music::Menu);
}

void StateMenu::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(mLogoSprite);
    //window.draw(mFire);
    //window.draw(mFire2);

    anax::World& world = *getContext().world;
    DrawEntetys drawEntetys;
    drawEntetys.draw(window,world);


    for (const sf::Text& text : mOptions)
        window.draw(text);
}

bool StateMenu::update(sf::Time)
{
    if(clock.getElapsedTime().asSeconds() > 0.1f)
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


    return true;
}

bool StateMenu::handleEvent(const sf::Event& event)
{

    if (event.type != sf::Event::KeyPressed)
    {
        if(event.type != sf::Event::MouseButtonPressed)
            return false;
    }

    if (event.key.code == sf::Keyboard::Return)
    {
        if (mOptionIndex == Play)
        {
            requestStateChange(States::Character);
        }
        else if (mOptionIndex == Settings)
        {
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

    else if (event.key.code == sf::Keyboard::Up)
    {
        if (mOptionIndex > 0)
            mOptionIndex--;
        else
            mOptionIndex = mOptions.size() - 1;

        updateOptionText();
        getContext().sounds->play(SoundEffects::Click);
    }

    else if (event.key.code == sf::Keyboard::Down)
    {
        if (mOptionIndex < mOptions.size() - 1)
            mOptionIndex++;
        else
            mOptionIndex = 0;

        updateOptionText();
        getContext().sounds->play(SoundEffects::Click);
    }

    else if(event.type == sf::Event::MouseButtonPressed)
    {
        anax::World& world = *getContext().world;
        sf::RenderWindow& window = *getContext().window;
        MouseClicked mouseClicked;
        mouseClicked.Clicked(world,sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);

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
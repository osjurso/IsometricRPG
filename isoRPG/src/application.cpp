#include <include/states/state_character.h>
#include <include/states/state_caracter_creation.h>
#include <include/states/state_game_over.h>
#include "include/states/state_menu.h"
#include "include/states/state_settings.h"
#include "include/states/state_game.h"
#include "include/states/state_pause.h"
#include "include/application.h"
#include "include/states/state_title.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
        : mWindow(sf::VideoMode(1920, 1080), "IsoRPG")
        , mTextures()
        , mFonts()
        , mWorld()
        , mMusic()
        , mSounds()
        , mStateStack(StateBase::Context(mWindow, mTextures, mFonts, mWorld, mMusic, mSounds))
        , mStatisticsText()
        , mStatisticsUpdateTime()
        , mStatisticsNumFrames(0)
        , mDebugMode(false)

{
    mFonts.load(Fonts::Main, "assets/fonts/Sansation.ttf");
    mFonts.load(Fonts::RPG, "assets/fonts/breathe_fire.otf");

    mTextures.load(Textures::Hero, "assets/textures/Hero_Clothes.png");
    mTextures.load(Textures::TitleLogo, "assets/textures/title-logo.png");
    mTextures.load(Textures::TitleText, "assets/textures/title-text.png");
    mTextures.load(Textures::MenuBackdrop, "assets/textures/menuBackdorp.png");
    mTextures.load(Textures::MenuFire, "assets/textures/fireSpriteSheet.png");
    mTextures.load(Textures::SettingsBackdorp, "assets/textures/settingsBackground.png");
    mTextures.load(Textures::SettingsSlider, "assets/textures/volumeslider.png");
    mTextures.load(Textures::SettingKnob, "assets/textures/volumeKnob.png");
    mTextures.load(Textures::CharacterBox, "assets/textures/characterBox.png");
    mTextures.load(Textures::CharacterNew, "assets/textures/button.png");
    mTextures.load(Textures::Goblin, "assets/textures/goblin.png");
    mTextures.load(Textures::Trader, "assets/textures/trader.png");
    mTextures.load(Textures::Armorer, "assets/textures/knight.png");
    mTextures.load(Textures::HeroHead,"assets/textures/Hero_Head.png");
    mTextures.load(Textures::HeroWeapon,"assets/textures/Hero_Longsword.png");
    mTextures.load(Textures::HeroShield,"assets/textures/Hero_Shield.png");
    mTextures.load(Textures::Tileset, "assets/map/spritesheet.png");

    mTextures.load(Textures::UIBottom, "assets/textures/UIBottom.png");
    mTextures.load(Textures::UIItems, "assets/textures/ui_modifiers.png");
    mTextures.load(Textures::UIConversation, "assets/textures/convoElement.png");
    mTextures.load(Textures::UIRedX, "assets/textures/redX.png");
    mTextures.load(Textures::UIAbilities, "assets/textures/alitities.png");
    mTextures.load(Textures::UIArrow, "assets/textures/arrow.png");
    mTextures.load(Textures::UIHealtBar, "assets/textures/healtbar.png");
    mTextures.load(Textures::UITransparant, "assets/textures/transparant.png");
    mTextures.load(Textures::TitleSword, "assets/textures/title_sword.png");
    mTextures.load(Textures::TitleSwordSplash, "assets/textures/title_sword_splash.png");
    mTextures.load(Textures::LightTexture, "assets/textures/light_texture.png");


    mStatisticsText.setFont(mFonts.get(Fonts::Main));
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(15);

    registerStates();
    mStateStack.pushState(States::Game);
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);

            if (mStateStack.isEmpty())
                mWindow.close();
        }
        updateStatistics(dt);
        render();
    }
}

void Application::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.key.code == sf::Keyboard::F3 && event.type == sf::Event::KeyPressed)
            mDebugMode = !mDebugMode;

        mStateStack.handleEvent(event);

        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Application::render()
{
    mWindow.clear();

    mStateStack.draw();

    mWindow.setView(mWindow.getDefaultView());
    if (mDebugMode)
        mWindow.draw(mStatisticsText);

    mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
    // TODO: Move FPS counter into its own util class
    mStatisticsUpdateTime += dt;
    mStatisticsNumFrames += 1;
    if (mStatisticsUpdateTime >= sf::seconds(1.0f))
    {
        mStatisticsText.setString("FPS: " + std::to_string(mStatisticsNumFrames));

        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}

void Application::registerStates()
{
    mStateStack.registerState<StateTitle>(States::Title);
    mStateStack.registerState<StateMenu>(States::Menu);
    mStateStack.registerState<StateSettings>(States::Settings);
    mStateStack.registerState<StateGame>(States::Game);
    mStateStack.registerState<StatePause>(States::Pause);
    mStateStack.registerState<StateCharacter>(States::Character);
    mStateStack.registerState<StateCaracterCreation>(States::CharacterCreation);
    mStateStack.registerState<StateGameOver>(States::GameOver);
}

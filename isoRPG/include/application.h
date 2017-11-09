#ifndef ISORPG_APPLICATION_H
#define ISORPG_APPLICATION_H

#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include <anax/World.hpp>

#include "include/gameEngine/state_stack.h"
#include "include/gameEngine/resource_holder.h"
#include "include/gameEngine/resource_identifiers.h"


class Application
{
public:
    Application();
    void run();


private:
    void processInput();
    void update(sf::Time dt);
    void render();

    void updateStatistics(sf::Time dt);
    void registerStates();


private:
    static const sf::Time TimePerFrame;

    sf::RenderWindow mWindow;
    anax::World mWorld;
    TextureHolder mTextures;
    FontHolder mFonts;
    MusicPlayer mMusic;
    SoundPlayer mSounds;

    StateStack mStateStack;

    bool mDebugMode;
    sf::Text mStatisticsText;
    sf::Time mStatisticsUpdateTime;
    std::size_t mStatisticsNumFrames;
};

#endif //ISORPG_APPLICATION_H

#ifndef ISORPG_APPLICATION_H
#define ISORPG_APPLICATION_H

#include <SFML/Graphics.hpp>

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
    TextureHolder mTextures;
    FontHolder mFonts;

    StateStack mStateStack;

    bool mDebugMode;
    sf::Text mStatisticsText;
    sf::Time mStatisticsUpdateTime;
    std::size_t mStatisticsNumFrames;
};

#endif //ISORPG_APPLICATION_H

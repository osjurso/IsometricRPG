#ifndef ISORPG_GAME_STATE_H
#define ISORPG_GAME_STATE_H

#include <list>

#include <SFML/Graphics.hpp>

#include "state_base.h"
#include "map/object.h"

class StateGame : public StateBase
{
public:
    StateGame(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event &event) override;

    void handleUserInput(sf::Keyboard::Key key, bool isPressed);

private:
    sf::View playerCam;
    anax::Entity player;
    sf::Clock movementTimer;
    sf::Clock pathfindingTimer;
    float zoom;
    int save = -1;
    std::string saveFile = "";
    sf::Clock saveTimer;
};


#endif //ISORPG_GAME_STATE_H

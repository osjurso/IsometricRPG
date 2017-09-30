#ifndef ISORPG_GAME_STATE_H
#define ISORPG_GAME_STATE_H

#include <list>

#include <SFML/Graphics.hpp>

#include "state_base.h"
#include "include/map/object.h"
#include "include/map/isometric_sprite.h"

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
    IsometricSprite mPlayer;
    bool isMovingUp, isMovingDown, isMovingLeft, isMovingRight;


protected:
    std::list<Object*> objects;
};


#endif //ISORPG_GAME_STATE_H

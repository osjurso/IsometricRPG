#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/System/Clock.hpp>
#include <states/state_base.h>

#include "map/object.h"

class Sprite : public Object
{
    // Map needs to access protected/private data
    friend class Map;

public:
    Sprite(TileSize tileSize, StateBase::Context context) : Object(tileSize, context) { }

    void process(float time);
    void draw(sf::RenderWindow& window);


protected:
    // Id of first tile
    int id;

    // Location on screen
    int x, y;

    // Current animation frame
    int frame;

    //Frame count (duh)
    int frameCount;

    // Length of one frame in ms
    int frameDuration;

    // Times the animation
    sf::Clock clock;

    bool test = true;
};

#endif
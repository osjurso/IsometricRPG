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

    void createEntities();


protected:
    // Id of first tile
    int id;

    // Location on screen
    int x, y;
};

#endif
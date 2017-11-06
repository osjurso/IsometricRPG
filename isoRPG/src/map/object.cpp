#include <SFML/Graphics.hpp>

#include "map/object.h"

Object::~Object()
{
    delete texture;
    texture = nullptr;
}

void Object::getTileCoords(int tile, int& x, int& y)
{
    // Tileid 0 means no tile, so the ids actually start from 1
    tile--;

    int tileXcount = texture->getSize().x / (64 + tileSize.s);

    x = (tile % tileXcount) * (64 + tileSize.s);
    y = (tile / tileXcount) * (64 + tileSize.s);
}

#include <SFML/Graphics.hpp>

#include "map/object.h"

void Object::IsometricToCartesian(sf::Vector2f& v)
{
    v = sf::Vector2f((2 * v.y + v.x) / 2, (2 * v.y - v.x) / 2);
}

void Object::IsometricToCartesian(sf::Vector2i& v)
{
    v = sf::Vector2i((2 * v.y + v.x) / 2, (2 * v.y - v.x) / 2);
}

void Object::CartesianToIsometric(sf::Vector2f& v)
{
    v = sf::Vector2f((v.x - v.y), (v.x + v.y)/2);
}

void Object::CartesianToIsometric(sf::Vector2i& v)
{
    v = sf::Vector2i((v.x - v.y), (v.x + v.y)/2);
}

Object::~Object()
{
    //delete texture;
    //texture = nullptr;
}

void Object::getTileCoords(int tile, int& x, int& y)
{
    // Tileid 0 means no tile, so the ids actually start from 1
    tile--;

    int tileXcount;

    if (tileset == "spritesheet")
        tileXcount = context.textures->get(Textures::grasslandTileset).getSize().x / (tileSize.x + tileSize.s);
    else if (tileset == "cave_tiles")
        tileXcount = context.textures->get(Textures::caveTileset).getSize().x / (tileSize.x + tileSize.s);

    x = (tile % tileXcount) * (tileSize.x + tileSize.s);
    y = (tile / tileXcount) * (tileSize.x + tileSize.s);
}

#ifndef OBJECT_H
#define OBJECT_H

#include <include/gameEngine/resource_identifiers.h>

namespace sf
{
    class RenderWindow;
    class Texture;
}

// Small helper struct that contains tile size information
struct TileSize
{
    int x; // Width
    int y; // Height
    int s; // Spacing
};

// Class representing any game object
class Object
{
    // Map needs to access protected/private data
    friend class Map;

public:
    Object(TileSize tileSize) : tileSize(tileSize) { }

    virtual ~Object();

    virtual void process(float deltaTime) {}
    virtual void draw(sf::RenderWindow& window) {}

    // Calculate x and y position of given tile in the texture
    void getTileCoords(int tile, int& x, int& y);

    void IsometricToCartesian(sf::Vector2f& v);
    void IsometricToCartesian(sf::Vector2i& v);
    void CartesianToIsometric(sf::Vector2f& v);
    void CartesianToIsometric(sf::Vector2i& v);

    const TileSize tileSize;

    int priority;

protected:
    sf::Texture* texture;
};

#endif

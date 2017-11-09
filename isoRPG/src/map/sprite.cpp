#include <SFML/Graphics.hpp>

#include "map/sprite.h"

void Sprite::process(float deltaTime)
{
    // Go to next animation frame if required
    if (clock.getElapsedTime().asMilliseconds() < frameDuration)
        return;

    if (++frame >= frameCount)
        frame = 0;

    clock.restart();
}

void Sprite::draw(sf::RenderWindow& window)
{
    int tilex, tiley;
    getTileCoords(id, tilex, tiley);

    // TODO: Using vertex arrays or permanent sprites would be faster
    sf::Sprite sprite(*texture, sf::IntRect(tilex + frame * (tileSize.x + tileSize.s), tiley, tileSize.x, tileSize.y));

    sprite.setOrigin(0, sprite.getGlobalBounds().height);

    //TODO: Braindead solution. Fix offset calculation
    if (tileSize.y == 64)
    {
        tilex = x + (16 * -1);
        tiley = y + (16 * 5);
    }
    else if (tileSize.y == 128)
    {
        tilex = x + (16 * 3);
        tiley = y + (16 * 13);
    }
    else if (tileSize.y == 192)
    {
        tilex = x + (16 * 7);
        tiley = y + (16 * 21);
    }
    else //tilesize.y == 256
    {
        tilex = x + (16 * 11);
        tiley = y + (16 * 29);
    }

    sf::Vector2f v(tilex, tiley);
    CartesianToIsometric(v);
    sprite.setPosition(v);

    priority = (int)(v.y);

    window.draw(sprite);
}

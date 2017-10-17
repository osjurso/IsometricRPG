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

    // Using vertex arrays or permanent sprites would be faster
    sf::Sprite sprite(*texture, sf::IntRect(tilex + frame * (tileSize.x + tileSize.s), tiley, tileSize.x, tileSize.y));

    // Adjusting coordinates because it places tiles based on texture origin (texture is 64x64),
    // instead of tilesize (64x32)
    tilex = x - 32;
    tiley = y + 32;

    // Converts screen position to world position
    sf::Vector2f v((tilex - tiley), (tilex + tiley)/2);
    sprite.setPosition(v);

    window.draw(sprite);
}

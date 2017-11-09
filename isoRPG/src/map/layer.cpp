#include <SFML/Graphics.hpp>

#include "map/layer.h"

void Layer::draw(sf::RenderWindow& window)
{
    sf::Vector2f center(window.getView().getCenter());
    sf::Vector2f viewSize(window.getView().getSize());

    //Getting cartesian coordinates to center
    sf::Vector2i midTile(static_cast<int>(center.x), static_cast<int>(center.y));
    //Dividing by tilesize to get tile at this poistion
    midTile = sf::Vector2i(midTile.x / (tileSize.x/2), midTile.y / (tileSize.y/2));
    //Calculating the Cartesian coordinates
    IsometricToCartesian(midTile);

    //TODO: ViewSize is in the wrong coordinate systems
    int xMax = (int) (midTile.x + ((viewSize.x / 2) / (tileSize.x / 3))); //Bottom right tile
    int xMin = (int) (midTile.x - ((viewSize.x / 2) / (tileSize.x / 3))); //Top left tile
    int yMax = (int) (midTile.y + ((viewSize.y / 2) / (tileSize.y / 5))); //Bottom left tile
    int yMin = (int) (midTile.y - ((viewSize.y / 2) / (tileSize.y / 5))); //Top right tile

    //Checking bounds
    if (xMin < 0) xMin = 0;
    if (xMax > width - 1) xMax = width - 1;
    if (yMin < 0) yMin = 0;
    if (yMax > height - 1) yMax = height - 1;

    // Render each tile in view
    for (int y = yMin; y < yMax; y++)
    {
        for (int x = xMin; x < xMax; x++)
        {
            //get the tileid (unique identifier for texture)
            int tileid = tilemap[x][y];

            // Skip empty tiles
            if (tilemap[x][y] == 0)
                continue;

            // Texture coordinates
            int tilex, tiley;
            getTileCoords(tileid, tilex, tiley);

            //TODO: Using vertex arrays or permanent sprites would be faster
            sf::Sprite sprite(*texture, sf::IntRect(tilex, tiley, tileSize.x, tileSize.y));

            sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);

            tilex = x * tileSize.x/2;
            tiley = y * tileSize.y/2;

            // Converts screen position to world position
            sf::Vector2f v((tilex - tiley), (tilex + tiley)/2);
            sprite.setPosition(v);

            window.draw(sprite);
        }
    }
}
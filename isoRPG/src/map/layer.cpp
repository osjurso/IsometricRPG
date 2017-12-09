#include <SFML/Graphics.hpp>
#include <collections/drawable.h>

#include "map/layer.h"

void Layer::createEntities()
{
    renderTexture.create(tileSize.x * width, tileSize.y * height);
    sf::View view = renderTexture.getView();

    // Centering the render texture canvas
    view.setCenter(0, 0);
    renderTexture.setView(view);

    // Render each tile in view
    for (int y = 0; y < width; y++)
    {
        for (int x = 0; x < height; x++)
        {
            //get the tileid (unique identifier for texture)
            int tileid = tilemap[x][y];

            // Skip empty tiles
            if (tilemap[x][y] == 0)
                    continue;

            // Texture coordinates
            int tilex, tiley;
            getTileCoords(tileid, tilex, tiley);

            sf::Sprite sprite(context.textures->get(Textures::Tileset), sf::IntRect(tilex, tiley, tileSize.x, tileSize.y));

            sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

            tilex = x * tileSize.x / 2;
            tiley = y * tileSize.y / 2;

            // Converts screen position to world position
            sf::Vector2f v((tilex - tiley), (tilex + tiley) / 2);
            sprite.setPosition(v);

            renderTexture.draw(sprite);
        }
    }
    // Flip the buffer
    renderTexture.display();

    // Create a sprite from the render texture
    sf::Sprite sprite;
    sprite.setTexture(renderTexture.getTexture());

    anax::World& world = *context.world;
    anax::Entity mapEntity = world.createEntity();

    Draweble draweble;

    // Position coordinates offsets the texture back
    draweble.makeDraweble(context.textures->get(Textures::Tileset), -(width*tileSize.x)/2, -(width*tileSize.y)/2, mapEntity, "Game");

    TextureComponent& textureComponent = mapEntity.getComponent<TextureComponent>();
    textureComponent.sprite[0] = sprite;
    textureComponent.sortKey = 0;
}
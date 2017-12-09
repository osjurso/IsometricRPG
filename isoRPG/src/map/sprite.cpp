#include <SFML/Graphics.hpp>

#include "map/sprite.h"
#include "collections/drawable.h"

void Sprite::createEntities()
{
        int tilex, tiley;
        getTileCoords(id, tilex, tiley);

        sf::IntRect tileRect = sf::IntRect(tilex, tiley, tileSize.x, tileSize.y);

        // Different offset for different sized tiles
        tilex = x + tileSize.y - 64;
        tiley = y + tileSize.y + tileSize.y - 64;

        sf::Vector2f v(tilex, tiley);
        CartesianToIsometric(v);

        sf::Sprite sprite = sf::Sprite(context.textures->get(Textures::Tileset), tileRect);
        sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height);
        anax::World& world = *context.world;

        Draweble draweble;

        anax::Entity mapEntity = world.createEntity();
        draweble.makeDraweble(context.textures->get(Textures::Tileset), v.x, v.y, mapEntity, "Game");

        TextureComponent& textureComponent = mapEntity.getComponent<TextureComponent>();
        textureComponent.sprite[0] = sprite;
        textureComponent.sortKey = static_cast<int>(mapEntity.getComponent<PositionComponent>().YPos);
}

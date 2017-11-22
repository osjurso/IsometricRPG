#include <SFML/Graphics.hpp>
#include <iostream>

#include "map/sprite.h"
#include "collections/drawable.h"


void Sprite::process(float deltaTime)
{
    // Go to next animation frame if required
    if (clock.getElapsedTime().asMilliseconds() < frameDuration)
        return;

    if (++frame >= frameCount)
        frame = 0;

    clock.restart();
}

void Sprite::draw()
{
    if (test)
    {
        int tilex, tiley;
        getTileCoords(id, tilex, tiley);

        sf::IntRect tileRect = sf::IntRect(tilex + frame * (tileSize.x + tileSize.s), tiley, tileSize.x, tileSize.y);

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

        sf::Sprite sprite = sf::Sprite(context.textures->get(Textures::Tileset), tileRect);
        sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height);
        anax::World& world = *context.world;

        Draweble draweble;

        anax::Entity mapEntity = world.createEntity();
        draweble.makeDraweble(context.textures->get(Textures::Tileset), v.x, v.y, mapEntity, "Game");

        TextureComponent& textureComponent = mapEntity.getComponent<TextureComponent>();
        textureComponent.sprite[0] = sprite;
        textureComponent.sortKey = mapEntity.getComponent<PositionComponent>().YPos;

        test = false;
    }
}
